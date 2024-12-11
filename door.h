
#ifndef DOOR_H
#define DOOR_H

#include <stdint.h>
#include "DIO.h"
#include "types.h"

//door states
#define DOOR_CLOSED 0
#define DOOR_OPEN   1


typedef struct {
    uint8_t state;         
    uint32_t openCount;    //  count # of times the door was opened
    uint32_t closeCount;   //  count # of times the door was closed
} DoorStatus;

// Function prototypes
void door_init(char port, uint8_t pin);
uint8_t door_get_status(char port, uint8_t pin);
void door_update_status(char port, uint8_t pin, DoorStatus* status);
void door_print_log(const DoorStatus* status); // ana 3iza a accsses el door status directlty mn el structure f ay t8ir hi7sl fe el members bto3 el struct gwa el function hism3 fe el memoey allocation 

#endif // DOOR_H
