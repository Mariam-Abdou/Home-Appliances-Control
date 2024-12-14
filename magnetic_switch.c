#include "magnetic_switch.h"

// Pointer to the interrupt callback function
static void (*interrupt_callback)(void) = 0;			
static uint8_t g_port;
static uint8_t g_pin;

uint32_t get_port_base(uint8_t port) {
    switch (port) {
        case 'A':
		case 'a':
			return GPIO_PORTA_BASE;
        case 'B':
		case 'b':
			return GPIO_PORTB_BASE;
        case 'C': 
		case 'c':
			return GPIO_PORTC_BASE;
        case 'D':
		case 'd':
			return GPIO_PORTD_BASE;
        case 'E':
		case 'e':
			return GPIO_PORTE_BASE;
        case 'F':
		case 'f':
			return GPIO_PORTF_BASE;
        default:	// Invalid port
			return 0;
    }
}

void magnetic_switch_init(uint8_t port, uint8_t pin){//, void (*callback)(void)) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return;
	
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
        case 'A': case 'a': SET_BIT(NVIC_EN0_R, 0);  break;
        case 'B': case 'b': SET_BIT(NVIC_EN0_R, 1);  break;
        case 'C': case 'c': SET_BIT(NVIC_EN0_R, 2);  break;
        case 'D': case 'd': SET_BIT(NVIC_EN0_R, 3);  break;
        case 'E': case 'e': SET_BIT(NVIC_EN0_R, 4);  break;
        case 'F': case 'f': SET_BIT(NVIC_EN0_R, 30); break;
    }

    //interrupt_callback = callback;    
}

uint8_t get_magnetic_switch_state(uint8_t port, uint8_t pin) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return 0xFF;
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
