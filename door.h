
#ifndef DOOR_H
#define DOOR_H

#include <stdint.h>
#include "DIO.h"
#include "types.h"

//door states
#define DOOR_CLOSED 0
#define DOOR_OPEN   1

uint8_t state; 



// Function prototypes
void door_init(char port, uint8_t pin);
uint8_t door_get_status(char port, uint8_t pin);
void door_update_status(char port, uint8_t pin, uint8_t status);

#endif // DOOR_H
