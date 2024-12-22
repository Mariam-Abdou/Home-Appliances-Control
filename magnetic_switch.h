#ifndef MAGNETIC_SWITCH_H
#define MAGNETIC_SWITCH_H

#include "tm4c123gh6pm.h"
#include "utils.h"
#include "DIO.h"

// Define the magnetic switch status
// OPEN: Indicates the switch is open (logic high)
// CLOSED: Indicates the switch is closed (logic low)
#define OPEN 1
#define CLOSED 0

// Register access macros
// These macros calculate the register address offsets for various GPIO interrupt-related registers.
#define GPIO_PORT_IS_R(port_base)   GPIO_PORT_REG(port_base, 0x404)  // Interrupt Sense register
#define GPIO_PORT_IBE_R(port_base)  GPIO_PORT_REG(port_base, 0x408)  // Interrupt Both Edges register
#define GPIO_PORT_IM_R(port_base)   GPIO_PORT_REG(port_base, 0x410)  // Interrupt Mask register
#define GPIO_PORT_RIS_R(port_base)  GPIO_PORT_REG(port_base, 0x414)  // Raw Interrupt Status register
#define GPIO_PORT_ICR_R(port_base)  GPIO_PORT_REG(port_base, 0x41C)  // Interrupt Clear register

// Function prototype
void magnetic_switch_init(uint8_t port, uint8_t pin, void (*callback)(void));
uint8_t get_magnetic_switch_state(uint8_t port, uint8_t pin);
void magnetic_switch_handler(void);

#endif // MAGNETIC_SWITCH_H
