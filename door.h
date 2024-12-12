#ifndef DOOR_H
#define DOOR_H

#include <stdint.h>
#include <stdbool.h>
#include "magnetic_switch.h"
#include "DIO.h"

// Door States
#define DOOR_OPEN   0
#define DOOR_CLOSED 1

// Function prototypes
void door_init(void);
void door_open(void);
void door_close(void);
void door_toggle(void);
void door_status(void);  // This function checks the door's current status (open/closed)
void door_magnetic_switch_callback(void);  // Callback for magnetic switch state change

#endif // DOOR_H
