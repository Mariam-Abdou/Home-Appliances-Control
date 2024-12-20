#include "bluetooth_module.h"


static void (*interrupt_callback)(void) = 0;  
void Bluetooth_Init(void (*callback)(void)) {
    UART0_Init();
    interrupt_callback = callback;
}

void Bluetooth_SendData(const uint8_t* data){
    UART0_TransmitString(data);
}

uint8_t Bluetooth_ReceiveData(void){
    return UART0_ReceiveChar();
}


void Bluetooth_Handler(void){
    // don't forget to clear the interrupt

    if (interrupt_callback  != 0)
        interrupt_callback();		
}