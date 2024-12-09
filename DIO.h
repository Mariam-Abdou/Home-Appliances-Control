#ifndef DIO_H
#define DIO_H

#include <stdint.h>
#include "tm4c123gh6pm.h"  

// Define the direction of a pin
#define OUTPUT 1
#define INPUT  0

// Define the mode of a pin
#define DIGITAL 1
#define ANALOG 0

// Define the pull-up or pull-down of a pin
#define PULL_UP 1
#define PULL_DOWN 0

// Define the unlock code
#define GPIO_LOCK_KEY 0x4C4F434B



// Define the pins
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

// Define the base addresses for each port
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
#define GPIO_PORT_DATA_R(port_base)      (*(volatile uint32_t *)(port_base + 0x3FC)) // Data register

// Function prototypes
void dio_init(char port, uint8_t pins, uint8_t direction, uint8_t pull, uint8_t digital);  
uint8_t dio_readpin(char port, uint8_t pin);
uint8_t dio_readport(char port);
void dio_writepin(char port, uint8_t pin, uint8_t value);
void dio_writeport(char port, uint8_t value);


#endif // DIO_H