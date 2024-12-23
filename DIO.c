#include "DIO.h"

/**
 * Function to get the base address of the specified port.
 *  port: The port identifier (e.g., PORT_A, PORT_B, etc.).
 * return: The base address of the GPIO port, or 0xFF if the port is invalid.
 */
uint32_t get_port_base(uint8_t port) {
    switch (port) {
        case PORT_A: return GPIO_PORTA_BASE;
        case PORT_B: return GPIO_PORTB_BASE;
        case PORT_C: return GPIO_PORTC_BASE;
        case PORT_D: return GPIO_PORTD_BASE;
        case PORT_E: return GPIO_PORTE_BASE;
        case PORT_F: return GPIO_PORTF_BASE;
        default: return 0xFF; // Invalid port identifier
    }
}

/**
 * Function to initialize a GPIO pin.
 *  port: The port identifier (e.g., PORT_A).
 *  pin: The pin number within the port (0-7).
 *  direction: The pin direction (1 for output, 0 for input).
 *  mode: The mode of the pin (1 for digital, 0 for analog).
 */
void dio_init(uint8_t port, uint8_t pin, uint8_t direction, uint8_t mode) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0xFF) return; // Exit if the port is invalid

    // Enable the clock for the specified port
    SET_BIT(SYSCTL_RCGCGPIO_R, port);
    while (GET_BIT(SYSCTL_PRGPIO_R, port) == 0); // Wait until the port is ready

    // Unlock mechanism for locked pins
    GPIO_PORT_LOCK_R(port_base) = GPIO_LOCK_KEY; // Unlock the port using the key
    SET_BIT(GPIO_PORT_CR_R(port_base), pin);     // Allow changes to the pin configuration

    // Set the pin direction (input or output)
    if (direction)
        SET_BIT(GPIO_PORT_DIR_R(port_base), pin); // Configure as output
    else
        CLEAR_BIT(GPIO_PORT_DIR_R(port_base), pin); // Configure as input

    // Configure the pin mode (digital or analog)
    if (mode)
        SET_BIT(GPIO_PORT_DEN_R(port_base), pin); // Enable digital functionality
    else
        CLEAR_BIT(GPIO_PORT_DEN_R(port_base), pin); // Enable analog functionality
}

/**
 * Function to configure the internal pull-up resistor for a pin.
 *  port: The port identifier (e.g., PORT_A).
 *  pin: The pin number within the port (0-7).
 *  pull: Enable or disable pull-up (1 to enable, 0 to disable).
 */
void dio_pull(uint8_t port, uint8_t pin, uint8_t pull) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0xFF) return; // Exit if the port is invalid

    if (pull)
        SET_BIT(GPIO_PORT_PUR_R(port_base), pin); // Enable pull-up resistor
    else
        CLEAR_BIT(GPIO_PORT_PUR_R(port_base), pin); // Disable pull-up resistor
}

/**
 * Function to read the value of a specific pin.
 *  port: The port identifier (e.g., PORT_A).
 *  pin: The pin number within the port (0-7).
 * return: The value of the pin (1 for high, 0 for low, or 0xFF if invalid).
 */
uint8_t dio_readpin(uint8_t port, uint8_t pin) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0xFF) return 0xFF; // Return 0xFF for invalid port

    return GET_BIT(GPIO_PORT_DATA_R(port_base), pin); // Read and return pin value
}

/**
 * Function to read the value of an entire port.
 *  port: The port identifier (e.g., PORT_A).
 * return: The value of the port (8-bit), or 0xFF if invalid.
 */
uint8_t dio_readport(uint8_t port) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0xFF) return 0xFF; // Return 0xFF for invalid port

    return (uint8_t)GPIO_PORT_DATA_R(port_base); // Read and return port value
}

/**
 * Function to write a value to a specific pin.
 *  port: The port identifier (e.g., PORT_A).
 *  pin: The pin number within the port (0-7).
 *  value: The value to write (1 for high, 0 for low).
 */
void dio_writepin(uint8_t port, uint8_t pin, uint8_t value) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0xFF) return; // Exit if the port is invalid

    if (value)
        SET_BIT(GPIO_PORT_DATA_R(port_base), pin); // Set pin high
    else
        CLEAR_BIT(GPIO_PORT_DATA_R(port_base), pin); // Set pin low
}

/**
 * Function to write a value to an entire port.
 *  port: The port identifier (e.g., PORT_A).
 *  value: The 8-bit value to write to the port.
 */
void dio_writeport(uint8_t port, uint8_t value) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0xFF) return; // Exit if the port is invalid

    GPIO_PORT_DATA_R(port_base) = value; // Write the value to the entire port
}
