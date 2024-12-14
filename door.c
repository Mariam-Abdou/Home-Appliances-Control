#include "door.h"

static uint8_t door_port;
static uint8_t door_pin;

void door_init(port, pin) {
	door_port, door_pin = port, pin;
    magnetic_switch_init(port, pin, door_callback);    
}

// Callback function to handle the magnetic switch state change
void door_callback(void) {
    uint8_t state = get_magnetic_switch_state(door_port, door_pin);

	if (state == CLOSED) {
		// If the magnetic switch is closed, closed door
	} else {
		// If the magnetic switch is open, open door
    }
}
