#include "door.h"
#include <stdio.h>


void door_init(char port, uint8_t pin) {
    dio_init(port, pin, INPUT, PULL_UP, DIGITAL); // pin -> input with pull-up resistor
}


uint8_t door_get_status(char port, uint8_t pin) {
    return dio_readpin(port, pin) ? DOOR_CLOSED : DOOR_OPEN; // depends on pin state
}


void door_update_status(char port, uint8_t pin, DoorStatus* status) {  //trigger an update 
    uint8_t currentStatus = door_get_status(port, pin);

    if (currentStatus != status->state) {
        if (currentStatus == DOOR_OPEN) { //pin reads 1 (logical high) when the switch is open (no magnet nearby).
            status->openCount++;
            printf("Door opened. Total opens: %lu\n", status->openCount);
        } else {
            status->closeCount++;  //When the magnetic switch is closed (magnet nearby), the pin reads 0 (logical low).
            printf("Door closed. Total closes: %lu\n", status->closeCount);
        }
        status->state = currentStatus;
    }
}

// Print the door status log////////////////////////////////////
void door_print_log(const DoorStatus* status) {
    printf("Door Status Log:\n");
    printf("State: %s\n", status->state == DOOR_OPEN ? "Open" : "Closed");
    printf("Open Count: %lu\n", status->openCount);
    printf("Close Count: %lu\n", status->closeCount);
}











/* 1-Structure for Door Status :
el structure holds el current state of the door (state), w el count of times the door opened feha (openCount),  ,, (closeCount).

   2-Saving the Door State:
The state  keeps track of whether the door is currently DOOR_OPEN or DOOR_CLOSED.

   3-Updating the Door State:
The door_update_status function checks the current state of the door using door_get_status.
If the current state is different from the saved state in the DoorStatus structure:
It updates the state in the structure.
Logs the event and increments the corresponding counter (openCount or closeCount).
 
   4-Event Logging:
Using the printf function, the system logs when the door is opened or closed along with the total counts for each action.

   5-Printing the Log:
The door_print_log function outputs the complete log of the door's activity, including its current state and the open/close counts.*/