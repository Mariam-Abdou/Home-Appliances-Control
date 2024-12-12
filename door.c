#include "door.h"

// Initialize the door system
void door_init(void) {
    // Initialize magnetic switch (assume connected to Port F, Pin 3)
    magnetic_switch_init('F', door_magnetic_switch_callback);  

    
}

// Callback function to handle the magnetic switch state change
void door_magnetic_switch_callback(void) {
    uint8_t state = magnetic_switch_get_state(MAGNETIC_SWITCH_PIN);
    
    if (state == MAGNETIC_SWITCH_CLOSED) {
        // If the magnetic switch is closed, close the door
       // door_close();
    } else {
        // If the magnetic switch is open, open the door
       // door_open();
    }
    
    }
