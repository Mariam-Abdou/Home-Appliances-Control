#include "door.h"
#include "bluetooth_module.h"
// Initialize the door system

void door_init(void) {
    Bluetooth_Init();
    magnetic_switch_init('F', door_magnetic_switch_callback);  

}

// Callback function to handle the magnetic switch state change
void door_magnetic_switch_callback(void) {
    uint8_t state = magnetic_switch_get_state(MAGNETIC_SWITCH_PIN);
    
    // Check Bluetooth connection status before sending
    if (Bluetooth_GetConnectionStatus() != BLUETOOTH_CONNECTED) {
        // Attempt to start pairing if not connected
        Bluetooth_StartPairing();
        return;
    }
    
    char* status_message;
    if (state == MAGNETIC_SWITCH_CLOSED) {
       status_message = "door closed";
    } else {
       status_message = "door open";
    }

    Bluetooth_SendData(status_message);
}

