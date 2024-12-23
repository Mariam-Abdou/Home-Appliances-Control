#include "bluetooth_module.h"


static void (*interrupt_callback)(void) = 0;  
void Bluetooth_Init(void (*callback)(void)) {
    UART0_Init();
    interrupt_callback = callback;
}

void Bluetooth_SendData(const uint8_t* data){
    UART0_TransmitString(data);
}

void Bluetooth_ReceiveData(uint8_t *str, uint32_t max_length) {
    UART0_ReceiveString(str, max_length);
}


uint8_t Bluetooth_ReceiveChar() {
    return UART0_ReceiveChar();
}


void Bluetooth_Handler(void){

    if(GET_BIT(UART0_MIS_R, UART0_MIS_R_RXMIS)) {  
      
    
      
         if (interrupt_callback  != 0)
         interrupt_callback();	 
      
      
      
        SET_BIT(UART0_ICR_R, UART0_ICR_R_RXIC);
    }

	
}