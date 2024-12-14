#ifndef BLUETOOTH_MODULE_H
#define BLUETOOTH_MODULE_H

#include <stdbool.h>

// Bluetooth Module Configuration Enum
typedef enum {
    BLUETOOTH_MODE_COMMAND,
    BLUETOOTH_MODE_DATA,
    BLUETOOTH_MODE_PAIRING
} BluetoothMode;

// Bluetooth Connection Status
typedef enum {
    BLUETOOTH_DISCONNECTED,
    BLUETOOTH_CONNECTED,
    BLUETOOTH_PAIRING
} BluetoothConnectionStatus;

// Bluetooth Module Initialization Function
void Bluetooth_Init(void);

// Set Bluetooth Operation Mode
bool Bluetooth_SetMode(BluetoothMode mode);

// Send AT Command to Bluetooth Module
bool Bluetooth_SendCommand(const char* command);

// Send Data via Bluetooth
bool Bluetooth_SendData(const char* data);

// Check Bluetooth Connection Status
BluetoothConnectionStatus Bluetooth_GetConnectionStatus(void);

// Start Bluetooth Pairing
bool Bluetooth_StartPairing(void);

// Stop Bluetooth Pairing
bool Bluetooth_StopPairing(void);

#endif // BLUETOOTH_MODULE_H