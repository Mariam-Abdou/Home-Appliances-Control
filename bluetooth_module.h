#ifndef BLUETOOTH_MODULE_H
#define BLUETOOTH_MODULE_H
#include "uart.h"

void Bluetooth_Init(void (*callback)(void));

void Bluetooth_SendData(const uint8_t* data);
uint8_t Bluetooth_ReceiveData(void);

void Bluetooth_Handler(void);

#endif // BLUETOOTH_MODULE_H