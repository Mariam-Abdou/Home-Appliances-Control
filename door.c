#include "door.h"
#include "bluetooth_module.h"


static uint8_t door_port;
static uint8_t door_pin;

void door_init(port, pin) {
	door_port, door_pin = port, pin;
    magnetic_switch_init(port, pin, door_callback);    

    //Bluetooth_Init();

}

// Callback function to handle the magnetic switch state change
void door_callback(void) {
    uint8_t state = get_magnetic_switch_state(door_port, door_pin);


    // // Check Bluetooth connection status before sending
    // if (Bluetooth_GetConnectionStatus() != BLUETOOTH_CONNECTED) {
    //     // Attempt to start pairing if not connected
    //     Bluetooth_StartPairing();
    //     return;
    // }

    char* status_message;
	if (state == CLOSED) {
       status_message = "door closed";
	} else {
       status_message = "door open";
    }



    //Bluetooth_SendData(status_message);
}

