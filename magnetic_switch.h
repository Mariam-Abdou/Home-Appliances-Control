#ifndef MAGNETIC_SWITCH_H
#define MAGNETIC_SWITCH_H

#include "tm4c123gh6pm.h"
#include "utils.h"
#include "DIO.h"

// Define the magnetic switch status
#define OPEN 1
#define CLOSED 0

// Register access macros
#define GPIO_PORT_IS_R(port_base)		GPIO_PORT_REG(port_base, 0x404)
#define GPIO_PORT_IBE_R(port_base)		GPIO_PORT_REG(port_base, 0x408)
#define GPIO_PORT_IM_R(port_base)		GPIO_PORT_REG(port_base, 0x410)
#define GPIO_PORT_RIS_R(port_base)		GPIO_PORT_REG(port_base, 0x414)
#define GPIO_PORT_ICR_R(port_base)		GPIO_PORT_REG(port_base, 0x41C)

// Function prototype
void magnetic_switch_init(uint8_t port, uint8_t pin, void (*callback)(void));
uint8_t get_magnetic_switch_state(uint8_t port, uint8_t pin);
void magnetic_switch_handler(void);

#endif // MAGNETIC_SWITCH_H
