#ifndef DOOR_H
#define DOOR_H

#include <stdint.h>
#include "DIO.h"
#include "magnetic_switch.h"

// Door States
#define OPEN   0
#define CLOSED 1

// Function prototypes
void door_init(void);
void door_callback(void);  // Callback for magnetic switch state change

#endif // DOOR_H
