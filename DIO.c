#include "DIO.h"

static uint32_t get_port_base(uint8_t port) {
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

void dio_init(uint8_t port, uint8_t pin, uint8_t direction, uint8_t mode) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return; // Invalid port check

    // Enable the clock for the port
    SET_BIT(SYSCTL_RCGCGPIO_R, (port - 'A'));   
    while ((SYSCTL_PRGPIO_R & (1U << (port - 'A'))) == 0); // Wait for the port to be ready

    // Unlock mechanism for locked pins
    GPIO_PORT_LOCK_R(port_base) = GPIO_LOCK_KEY;	// Unlock the port
    SET_BIT(GPIO_PORT_CR_R(port_base), pin);		// Commit register for the pin
    
    // Set the direction of the pin
    if (direction)
        SET_BIT(GPIO_PORT_DIR_R(port_base), pin);
	else
		CLEAR_BIT(GPIO_PORT_DIR_R(port_base), pin);  

    // Set the mode of the pin (digital or analog)
    if(mode)
        SET_BIT(GPIO_PORT_DEN_R(port_base), pin);
    else
        CLEAR_BIT(GPIO_PORT_DEN_R(port_base), pin);
}

void dio_pull(uint8_t port, uint8_t pin, uint8_t pull) {
	uint32_t port_base = get_port_base(port);
    if (port_base == 0) return;
	
	if(pull)
		SET_BIT(GPIO_PORT_PUR_R(port_base), pin);
	else
		CLEAR_BIT(GPIO_PORT_PUR_R(port_base), pin);
}

uint8_t dio_readpin(uint8_t port, uint8_t pin) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return 0xFF;

    return GET_BIT(GPIO_PORT_DATA_R(port_base), pin);
}

uint8_t dio_readport(uint8_t port) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return 0xFF;

    return (uint8_t) GPIO_PORT_DATA_R(port_base);
}

void dio_writepin(uint8_t port, uint8_t pin, uint8_t value) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return;
    
	if (value)
        SET_BIT(GPIO_PORT_DATA_R(port_base), pin);
    else
        CLEAR_BIT(GPIO_PORT_DATA_R(port_base), pin);
}

void dio_writeport(uint8_t port, uint8_t value) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return; 
    
    GPIO_PORT_DATA_R(port_base) = value;
}