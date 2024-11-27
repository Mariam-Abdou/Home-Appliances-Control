#ifndef DIO_H
#define DIO_H

#include <stdint.h>
#include "TM4C123GH6PM.h"  //This file contains essential definitions and declarations that help you program the microcontroller. 
                           //(Hardware Constants , Interrupt Definitions ,Register and Peripheral Definitions,Clock System Configuration,GPIO Pin Configurations)

// Define direction constants for Input and Output
#define Output 1
#define Input  0

#define Digital 1
#define Analog 0

#define PullUp 1
#define PullDown 0
// Pin mask values (example for Pin0 and Pin1)
//These macros represent individual pins as bit masks. In microcontroller programming,
// registers are often manipulated at the bit level to control specific pins of a GPIO port.
// These definitions make it easy to refer to individual pins using their names (Pin0, Pin1, etc.) rather than raw numbers.
#define Pin0   (1U << 0)
#define Pin1   (1U << 1)
#define Pin2   (1U << 2)
#define Pin3   (1U << 3)
#define Pin4   (1U << 4)
#define Pin5   (1U << 5)
#define Pin6   (1U << 6)
#define Pin7   (1U << 7)

// GPIO port base addresses
//Each port (e.g., A, B, C, etc.) is managed by a separate set of registers. 
//The base address indicates the start of these registers, and offsets are added to access specific functionalities within the port (like mode settings, output data, etc.).
#define GPIO_PORTA_BASE  0x40004000
#define GPIO_PORTB_BASE  0x40005000
#define GPIO_PORTC_BASE  0x40006000
#define GPIO_PORTD_BASE  0x40007000
#define GPIO_PORTE_BASE  0x40024000
#define GPIO_PORTF_BASE  0x40025000

// Define the necessary registers for each port
#define GPIO_PORT_DIR_R(port_base)       (*(volatile uint32_t *)(port_base + 0x400))  // Direction register
#define GPIO_PORT_DEN_R(port_base)       (*(volatile uint32_t *)(port_base + 0x51C))  // Digital enable register
#define GPIO_PORT_PUR_R(port_base)       (*(volatile uint32_t *)(port_base + 0x510))  // Pull-up resistor register
#define GPIO_PORT_LOCK_R(port_base)      (*(volatile uint32_t *)(port_base + 0x520))  // Lock register
#define GPIO_PORT_CR_R(port_base)        (*(volatile uint32_t *)(port_base + 0x524))  // Commit register
#define GPIO_PORT_DATA_BITS_R(port_base) ((volatile uint32_t *)(port_base))           // Data bits register

// Function prototypes
void dio_init(char port, uint8_t pins, uint8_t direction, uint8_t pull, uint8_t digital); //initlization 
uint8_t dio_readpin(char port, uint8_t pin);//Reads the current state of a pin.
uint8_t dio_readport(char port);
void dio_writepin(char port, uint8_t pin, uint8_t value); //Sets a pin HIGH or LOW.
void dio_writeport(char port, uint8_t value);


#endif // DIO_H