#include "magnetic_switch.h"

// Pointer to the interrupt callback function
static void (*interrupt_callback)(void) = 0;			
static uint8_t g_port;
static uint8_t g_pin;

void magnetic_switch_init(uint8_t port, uint8_t pin, void (*callback)(void)) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0xFF) return;
	
    dio_init(port, pin, IN, DIGITAL);
	dio_pull(port, pin, UP);

	// Store global interrupt details
    g_port = port;
    g_pin = pin;			//let equal port base?

    // Configure GPIO interrupt settings
    CLEAR_BIT(GPIO_PORT_IM_R(port_base), pin);		// Disable interrupt for the pin
    CLEAR_BIT(GPIO_PORT_IS_R(port_base), pin);		// Edge-sensitive interrupt
    SET_BIT(GPIO_PORT_IBE_R(port_base), pin);		// Interrupt on both edges
    SET_BIT(GPIO_PORT_ICR_R(port_base), pin);		// Clear any prior interrupts
    SET_BIT(GPIO_PORT_IM_R(port_base), pin);		// Enable interrupt for the pin
	
	switch(port) {
        case PORT_A: SET_BIT(NVIC_EN0_R, 0);  break;
        case PORT_B: SET_BIT(NVIC_EN0_R, 1);  break;
        case PORT_C: SET_BIT(NVIC_EN0_R, 2);  break;
        case PORT_D: SET_BIT(NVIC_EN0_R, 3);  break;
        case PORT_E: SET_BIT(NVIC_EN0_R, 4);  break;
        case PORT_F: SET_BIT(NVIC_EN0_R, 30); break;
    }

    interrupt_callback = callback;
}

uint8_t get_magnetic_switch_state(uint8_t port, uint8_t pin) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0xFF) return 0xFF;
    return dio_readpin(port, pin);
}

// GPIO Port ISR
void magnetic_switch_handler(void) {
    uint32_t port_base = get_port_base(g_port);

	// Check if interrupt was triggered
    if (GET_BIT(GPIO_PORT_RIS_R(port_base), g_pin)) {
		// Set interrupt clear register (ICR) to clear the interrupt flag
        SET_BIT(GPIO_PORT_ICR_R(port_base), g_pin);
        
        if (interrupt_callback != 0)
            interrupt_callback();		// Call the user-defined callback function
    }
}
