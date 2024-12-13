#include "magnetic_switch.h"

// Pointer to the interrupt callback function
static void (*interrupt_callback)(void) = NULL;  
static uint8_t g_interrupt_port;
static uint8_t g_interrupt_pin;

void magnetic_switch_init(uint8_t port, uint8_t pin, void (*callback)(void)) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return;
	
    dio_init(port, pin, IN, DIGITAL);
	dio_pull(port, pin, DOWN);

	// Store global interrupt details
    g_interrupt_port = port;
    g_interrupt_pin = pin;			//let equal port base?

    // Configure GPIO interrupt settings
    CLEAR_BIT(GPIO_PORT_IM_R(port_base), pin);  // Disable interrupt for the pin
    CLEAR_BIT(GPIO_PORT_IS_R(port_base), pin);    // Edge-sensitive interrupt
    SET_BIT(GPIO_PORT_IBE_R(port_base), pin);   // Interrupt on both edges
    SET_BIT(GPIO_PORT_ICR_R(port_base), pin);   // Clear any prior interrupts
    SET_BIT(GPIO_PORT_IM_R(port_base), pin);    // Enable interrupt for the pin
	
	switch(port) {
        case PORT_A: NVIC_EN0_R |= (1 << 0);  break;
        case PORT_B: NVIC_EN0_R |= (1 << 1);  break;
        case PORT_C: NVIC_EN0_R |= (1 << 2);  break;
        case PORT_D: NVIC_EN0_R |= (1 << 3);  break;
        case PORT_E: NVIC_EN0_R |= (1 << 4);  break;
        case PORT_F: NVIC_EN0_R |= (1 << 30); break;
    }

    interrupt_callback = callback;    
}

uint8_t magnetic_switch_get_state(uint8_t port, uint8_t pin) {
	uint32_t port_base = get_port_base(port);
    if (port_base == 0) return 0;
    return dio_readpin(port, pin);  
}

// Generic GPIO Port ISR
void magnetic_switch_handler() {
    uint32_t port_base = get_port_base(g_interrupt_port);

	// Check if interrupt was triggered
    if (GET_BIT(GPIO_PORT_RIS_R(port_base), g_interrupt_pin)) {
		// Clear the interrupt flag
        SET_BIT(GPIO_PORTF_ICR_R(port_base), g_interrupt_pin);
        
        if (interrupt_callback != NULL)
            interrupt_callback();		// Call the user-defined callback function
    }
}

