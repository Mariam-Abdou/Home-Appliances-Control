#include "door2.h"
#include <stdio.h>

// Global variable to track previous door state
static uint8_t previous_door_state = MAGNETIC_SWITCH_OPEN;

// Initialize the door system
void door_init(void) {
    // Initialize magnetic switch on port F
    magnetic_switch_init('D');  
}

// Polling function to check door state
void door_check_state(void) {
    // Get current magnetic switch state
    uint8_t current_door_state = magnetic_switch_get_state(MAGNETIC_SWITCH_PIN);
    dio_init('F', 3, OUTPUT, PULL_DOWN, DIGITAL);
    dio_init('F', 2, OUTPUT, PULL_DOWN, DIGITAL);
    // Check if state has changed
    if (current_door_state != previous_door_state) {
        // Print status based on current state
        if (current_door_state == MAGNETIC_SWITCH_CLOSED) {
            printf("door closed\n");
            dio_writepin('F', 2, 1);
            
        } else {
            printf("door open\n");
            dio_writepin('F', 2, 0);
        }
        
        // Update previous state
        previous_door_state = current_door_state;
    }
}

