#include "magnetic_switch.h"

// Pointer to the interrupt callback function
static void (*interrupt_callback)(void) = 0; // Callback function for the interrupt

// Global variables to store the port and pin configuration
static uint8_t g_port;
static uint8_t g_pin;

/**
 * Initialize the magnetic switch with the given port and pin.
 * Configures the pin as an input with a pull-up resistor and sets up the interrupt.
 *  port: The GPIO port identifier (e.g., PORT_A).
 *  pin: The pin number within the port (0-7).
 *  callback: Pointer to the callback function to execute on interrupt.
 */
void magnetic_switch_init(uint8_t port, uint8_t pin, void (*callback)(void)) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0xFF) return; // Exit if the port is invalid

    // Initialize the pin as input with pull-up resistor
    dio_init(port, pin, IN, DIGITAL);
    dio_pull(port, pin, UP);

    // Store global interrupt configuration
    g_port = port;
    g_pin = pin;

    // Configure GPIO interrupt settings
    CLEAR_BIT(GPIO_PORT_IM_R(port_base), pin); // Disable interrupt for the pin during setup
    CLEAR_BIT(GPIO_PORT_IS_R(port_base), pin); // Set to edge-sensitive interrupt
    SET_BIT(GPIO_PORT_IBE_R(port_base), pin);  // Enable interrupt on both edges (rising and falling)
    SET_BIT(GPIO_PORT_ICR_R(port_base), pin);  // Clear any prior interrupt flags
    SET_BIT(GPIO_PORT_IM_R(port_base), pin);   // Enable interrupt for the pin

    // Enable the corresponding NVIC interrupt for the port
    switch (port) {
        case PORT_A: SET_BIT(NVIC_EN0_R, 0);  break;
        case PORT_B: SET_BIT(NVIC_EN0_R, 1);  break;
        case PORT_C: SET_BIT(NVIC_EN0_R, 2);  break;
        case PORT_D: SET_BIT(NVIC_EN0_R, 3);  break;
        case PORT_E: SET_BIT(NVIC_EN0_R, 4);  break;
        case PORT_F: SET_BIT(NVIC_EN0_R, 30); break;
    }

    // Assign the user-defined callback function
    interrupt_callback = callback;
}

/**
 * Get the current state of the magnetic switch.
 *  port: The GPIO port identifier (e.g., PORT_A).
 *  pin: The pin number within the port (0-7).
 *return: The current state of the pin (1 for high, 0 for low, or 0xFF if invalid).
 */
uint8_t get_magnetic_switch_state(uint8_t port, uint8_t pin) {
    uint32_t port_base = get_port_base(port);
    if (port_base == 0xFF) return 0xFF; // Return 0xFF for invalid port

    return dio_readpin(port, pin); // Return the current state of the pin
}

/**
 * Interrupt Service Routine (ISR) for the magnetic switch.
 * Handles the GPIO interrupt, clears the interrupt flag, and calls the user-defined callback function.
 */
void magnetic_switch_handler(void) {
    // Clear the interrupt flag for the specific pin
    uint32_t port_base = get_port_base(g_port);
    if (port_base == 0xFF) return; // Exit if port_base is invalid

    SET_BIT(GPIO_PORT_ICR_R(port_base), g_pin); // Clear the interrupt flag

    // Execute the callback function if defined
    if (interrupt_callback != 0) {
        interrupt_callback(); // Call the user-defined interrupt handler
    }
}
