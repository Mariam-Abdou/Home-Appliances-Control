#ifndef BLUETOOTH_MODULE_H
#define BLUETOOTH_MODULE_H
#include "uart.h"

void Bluetooth_Init(void (*callback)(void));

void Bluetooth_SendData(const uint8_t* data);
void Bluetooth_ReceiveData(uint8_t *str, uint32_t max_length);

//void Bluetooth_Handler(void);

#endif // BLUETOOTH_MODULE_H