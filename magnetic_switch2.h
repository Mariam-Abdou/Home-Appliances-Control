#ifndef MAGNETIC_SWITCH_H
#define MAGNETIC_SWITCH_H

#include <stdint.h>
#include <stdbool.h>
#include "DIO.h"

// Define possible states for the magnetic switch
#define MAGNETIC_SWITCH_OPEN  0
#define MAGNETIC_SWITCH_CLOSED 1


#define MAGNETIC_SWITCH_PIN  PIN3
#define MAGNETIC_SWITCH_PORT GPIO_PORTD_BASE 

// Function prototype

uint8_t magnetic_switch_init(char port);
uint8_t magnetic_switch_get_state(uint8_t pin);
void magnetic_switch_handler(uint8_t pin);
#endif // MAGNETIC_SWITCH_H
