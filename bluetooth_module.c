#include "bluetooth_module.h"
#include "uart.h"
#include <string.h>

// Internal Bluetooth Module State
static struct {
    BluetoothMode currentMode;
    BluetoothConnectionStatus connectionStatus;
} bluetoothState;

// Initialize Bluetooth Module
void Bluetooth_Init(void) {
    // Use the UART initialization with a callback
    UART0_Init(bluetooth_callback);  // You can add a specific callback if needed
    
    // Default mode setup
    bluetoothState.currentMode = BLUETOOTH_MODE_COMMAND;
    bluetoothState.connectionStatus = BLUETOOTH_DISCONNECTED;
    
    // Send initial AT commands to configure module
    Bluetooth_SendCommand("AT");  // Basic AT command to check module
    Bluetooth_SendCommand("AT+ROLE=0");  // Set as slave mode
    Bluetooth_SendCommand("AT+RESET");   // Reset module
}

// Set Bluetooth Operation Mode
bool Bluetooth_SetMode(BluetoothMode mode) {
    switch(mode) {
        case BLUETOOTH_MODE_COMMAND:
            Bluetooth_SendCommand("AT");
            break;
        case BLUETOOTH_MODE_DATA:
            Bluetooth_SendCommand("AT+DATAMODE");
            break;
        case BLUETOOTH_MODE_PAIRING:
            return Bluetooth_StartPairing();
        default:
            return false;
    }
    
    bluetoothState.currentMode = mode;
    return true;
}

// Send AT Command to Bluetooth Module
bool Bluetooth_SendCommand(const char* command) {
    // Ensure we're in command mode
    bluetoothState.currentMode = BLUETOOTH_MODE_COMMAND;
    
    // Send command with CR/LF
    char fullCommand[64];
    snprintf(fullCommand, sizeof(fullCommand), "%s\r\n", command);
    UART0_TransmitString(fullCommand);
    
    // TODO: Add response checking mechanism
    return true;
}

// Send Data via Bluetooth
bool Bluetooth_SendData(const char* data) {
    // Ensure we're in data mode
    if (bluetoothState.connectionStatus != BLUETOOTH_CONNECTED) {
        return false;
    }
    
    bluetoothState.currentMode = BLUETOOTH_MODE_DATA;
    UART0_TransmitString(data);
    
    return true;
}

// Check Bluetooth Connection Status
BluetoothConnectionStatus Bluetooth_GetConnectionStatus(void) {
    // Send status query command
    Bluetooth_SendCommand("AT+STATUS");
    
    // TODO: Parse response to update connectionStatus
    return bluetoothState.connectionStatus;
}

// Start Bluetooth Pairing
bool Bluetooth_StartPairing(void) {
    bluetoothState.currentMode = BLUETOOTH_MODE_PAIRING;
    bluetoothState.connectionStatus = BLUETOOTH_PAIRING;
    
    Bluetooth_SendCommand("AT+PAIR");
    
    return true;
}

// Stop Bluetooth Pairing
bool Bluetooth_StopPairing(void) {
    bluetoothState.currentMode = BLUETOOTH_MODE_COMMAND;
    bluetoothState.connectionStatus = BLUETOOTH_DISCONNECTED;
    
    Bluetooth_SendCommand("AT+CANCELPAIR");
    
    return true;
}

void bluetooth_callback(char receivedChar) {
    if (receivedChar == 'A') {
        // Send a response back to Bluetooth device when 'A' is received
        UART_HC05_TransmitString("Received A command\n");
    } else if (receivedChar == 'B') {
        // Send another response when 'B' is received
        UART_HC05_TransmitString("Received B command\n");
    } else {
        // Echo the received character if it's not 'A' or 'B'
        UART_HC05_TransmitChar(receivedChar);
    }
}