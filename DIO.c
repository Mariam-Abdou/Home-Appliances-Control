#include "DIO.h"
#include "bitwise_operation.h"


//noteeees: make switch func coz dup
// port_data instead of port_base
// ctz




// Function to count trailing zeros
uint8_t ctz(uint32_t value) {
    uint8_t count = 0;
    if (value == 0) return 32; // Special case: if the value is 0, return 32
    while ((value & 1) == 0) { // Check if the least significant bit is 0
        count++;
        value >>= 1; // Right shift the value to check the next bit
    }
    return count;
}

// Function to initialize a port and pins
void DIO_Init(char port, uint8_t pins, uint8_t direction, uint8_t pull, uint8_t digital) {
    uint32_t port_base = 0;

    // Select base address based on port letter
    switch (port) {
        case 'A': port_base = GPIO_PORTA_BASE; break;
        case 'B': port_base = GPIO_PORTB_BASE; break;
        case 'C': port_base = GPIO_PORTC_BASE; break;
        case 'D': port_base = GPIO_PORTD_BASE; break;
        case 'E': port_base = GPIO_PORTE_BASE; break;
        case 'F': port_base = GPIO_PORTF_BASE; break;
        default: return;  // Invalid port
    }

    // Enable the clock for the port
    SYSCTL_RCGCGPIO_R |= (1U << (port - 'A'));      
      

    SET_BITS(SYSCTL_RCGCGPIO_R, (1U << (port - 'A'))); 
    //SET_BIT(SYSCTL_RCGCGPIO_R, (port - 'A'));     //old 



    while ((SYSCTL_PRGPIO_R & (1U << (port - 'A'))) == 0);

    // Unlock mechanism for locked pins
    if (port == 'F' && (pins & Pin0)) {  // Check if PF0 is part of the pins
        GPIO_PORT_LOCK_R(port_base) = 0x4C4F434B;  // Unlock the port
        SET_BITS(GPIO_PORT_CR_R(port_base), pins);        // Commit register for the pins
    }

    // Configure the pins as input or output
    if (direction == Output) {
        SET_BITS(GPIO_PORT_DIR_R(port_base), pins);  // Set pins as output
    } else if (direction == Input) {
        CLEAR_BITS(GPIO_PORT_DIR_R(port_base), pins);  // Set pins as input 3shan if new writtem

        // Enable pull-up resistors for the input pins
        if(pull)
            SET_BITS(GPIO_PORT_PUR_R(port_base), pins);
        else
            CLEAR_BITS(GPIO_PORT_PUR_R(port_base), pins);
    }

    // Enable the digital functionality for the pins
    if(digital)
        SET_BITS(GPIO_PORT_DEN_R(port_base), pins);
    else
        CLEAR_BITS(GPIO_PORT_DEN_R(port_base), pins);
}

// Function to read a specific pin
uint8_t DIO_ReadPin(char port, uint8_t pin) {
    uint32_t port_base = 0;

    // Select base address based on port letter
    switch (port) {
        case 'A': port_base = GPIO_PORTA_BASE; break;
        case 'B': port_base = GPIO_PORTB_BASE; break;
        case 'C': port_base = GPIO_PORTC_BASE; break;
        case 'D': port_base = GPIO_PORTD_BASE; break;
        case 'E': port_base = GPIO_PORTE_BASE; break;
        case 'F': port_base = GPIO_PORTF_BASE; break;
        default: return 0;  // Invalid port check
    }

    // Read the pin's value
    //return GET_BIT(*(volatile uint32_t *)(port_base + 0x3FC), ctz(pin));  //old
    return GET_BITS(*(volatile uint32_t *)(port_base + 0x3FC), pin);
}

// Function to read the entire port
uint8_t DIO_ReadPort(char port) {
    uint32_t port_base = 0;

    // Select base address based on port letter
    switch (port) {
        case 'A': port_base = GPIO_PORTA_BASE; break;
        case 'B': port_base = GPIO_PORTB_BASE; break;
        case 'C': port_base = GPIO_PORTC_BASE; break;
        case 'D': port_base = GPIO_PORTD_BASE; break;
        case 'E': port_base = GPIO_PORTE_BASE; break;
        case 'F': port_base = GPIO_PORTF_BASE; break;
        default: return 0;  // Invalid port check
    }

    // Read the entire port's value
    return (uint8_t)(*(volatile uint32_t *)(port_base + 0x3FC));
}

// Function to write to a specific pin
void DIO_WritePin(char port, uint8_t pin, uint8_t value) {
    uint32_t port_base = 0;

    // Select base address based on port letter
    switch (port) {
        case 'A': port_base = GPIO_PORTA_BASE; break;
        case 'B': port_base = GPIO_PORTB_BASE; break;
        case 'C': port_base = GPIO_PORTC_BASE; break;
        case 'D': port_base = GPIO_PORTD_BASE; break;
        case 'E': port_base = GPIO_PORTE_BASE; break;
        case 'F': port_base = GPIO_PORTF_BASE; break;
        default: return;  // Invalid port check
    }

    // Write value to the pin
    if (value) {
        //SET_BIT(*(volatile uint32_t *)(port_base + (1U << (2 + ctz(pin)))), ctz(pin));   //old
        SET_BITS(*(volatile uint32_t *)(port_base + pin << 2), pin);

    } else {
        //CLEAR_BIT(*(volatile uint32_t *)(port_base + (1U << (2 + ctz(pin)))), ctz(pin)); //old
        CLEAR_BITS(*(volatile uint32_t *)(port_base + pin << 2), pin);

    }
}


// Function to write to the entire port
void DIO_WritePort(char port, uint8_t value) {
    uint32_t port_base = 0;

    // Select base address based on port letter
    switch (port) {
        case 'A': port_base = GPIO_PORTA_BASE; break;
        case 'B': port_base = GPIO_PORTB_BASE; break;
        case 'C': port_base = GPIO_PORTC_BASE; break;
        case 'D': port_base = GPIO_PORTD_BASE; break;
        case 'E': port_base = GPIO_PORTE_BASE; break;
        case 'F': port_base = GPIO_PORTF_BASE; break;
        default: return;  // Invalid port check
    }

    // Write the entire port's value
    *(volatile uint32_t *)(port_base + 0x3FC) = value;
}