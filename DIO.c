#include "DIO.h"
#include "bitwise_operation.h"



uint32_t get_port_base(char port) {
    switch (port) {
        case 'A': return GPIO_PORTA_BASE;
        case 'B': return GPIO_PORTB_BASE;
        case 'C': return GPIO_PORTC_BASE;
        case 'D': return GPIO_PORTD_BASE;
        case 'E': return GPIO_PORTE_BASE;
        case 'F': return GPIO_PORTF_BASE;
        default: return 0; // Invalid port
    }
}



void dio_init(char port, uint8_t pin, uint8_t direction, uint8_t pull, uint8_t digital) {

    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return; // Invalid port check


    // Enable the clock for the port
    SET_BIT(SYSCTL_RCGCGPIO_R, (port - 'A'));   

    while ((SYSCTL_PRGPIO_R & (1U << (port - 'A'))) == 0); // Wait for the port to be ready

    // Unlock mechanism for locked pins
    GPIO_PORT_LOCK_R(port_base) = GPIO_LOCK_KEY;  // Unlock the port
    SET_BIT(GPIO_PORT_CR_R(port_base), pin);   // Commit register for the pin
    

    // Set the direction of the pin (input or output)
    if (direction == INPUT) {
        CLEAR_BIT(GPIO_PORT_DIR_R(port_base), pin);  

        // Set the pull-up or pull-down
        if(pull)
            SET_BIT(GPIO_PORT_PUR_R(port_base), pin);
        else
            CLEAR_BIT(GPIO_PORT_PUR_R(port_base), pin);
    } 
    else
        SET_BIT(GPIO_PORT_DIR_R(port_base), pin);  
    
 


    // Set the mode of the pin (digital or analog)
    if(digital)
        SET_BIT(GPIO_PORT_DEN_R(port_base), pin);
    else
        CLEAR_BIT(GPIO_PORT_DEN_R(port_base), pin);



}


uint8_t dio_readpin(char port, uint8_t pin) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return 0xFF; // Invalid port check //?

    return GET_BIT(GPIO_PORT_DATA_R(port_base), pin);
}


uint8_t dio_readport(char port) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return 0xFF; // Invalid port check //?

    // Read the port's value (from pins 0 to 7)
    return (uint8_t) GPIO_PORT_DATA_R(port_base);
}


void dio_writepin(char port, uint8_t pin, uint8_t value) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return; // Invalid port check


    
    // if (value) {
    //     // SET_BIT(*(volatile uint32_t *)(port_base + pin << 2), pin); 
    //     GPIO_PORT_DATA_BITS_R(port_base)[pin] = 1; //?

    // } else {
    //     // CLEAR_BIT(*(volatile uint32_t *)(port_base + pin << 2), pin); 
    //     GPIO_PORT_DATA_BITS_R(port_base)[pin] = 0; //?

    // } // ?

    if(value)
        SET_BIT(GPIO_PORT_DATA_BITS_R(port_base)[pin], pin);
    else
        CLEAR_BIT(GPIO_PORT_DATA_BITS_R(port_base)[pin], pin);
    //value = (value != 0) ? 1 : 0; // Make sure the value is either 0 or 1

    // Write the value to the pin
    GPIO_PORT_DATA_BITS_R(port_base)[pin] = value;


}


void dio_writeport(char port, uint8_t value) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0) return; // Invalid port check

    
    //value = (value != 0) ? 1 : 0; // Make sure the value is either 0 or 1

    // Write value to the port
    GPIO_PORT_DATA_R(port_base) = value;
}