#include "lamp_plug.h"
#include "uart.h"
#include "dio.h"



int main(void) {
    uint8_t lamp_port = PORT_B; 
    uint8_t lamp_pin = 2; 

    uint8_t switch_port = PORT_C; 
    uint8_t switch_pin = 4; 
    
    uint8_t plug_port = PORT_D; 
    uint8_t plug_pin = 2; 

    uint8_t switch_plug_port = PORT_C; 
    uint8_t switch_plug_pin = 0; 


   // UART0_Init(); 
     lamp_init(lamp_port, lamp_pin);
     switch_init(switch_port, switch_pin);
     plug_init(plug_port, plug_pin);
     switch_init(switch_plug_port, switch_plug_pin);
     uint8_t switch_state, app_signal, switch_plug_state, app_signal2;
     
     
    while (1) {
        switch_state = switch_get(switch_port, switch_pin); 
        app_signal = UART0_ReceiveChar();  // nope Receive mn blutooth 
        lamp_update_state(lamp_port, lamp_pin, switch_state, app_signal);  
        switch_plug_state = switch_get(switch_plug_port, switch_plug_pin);
        app_signal2 = UART0_ReceiveChar();  // blutooth
        plug_update_state(lamp_port, lamp_pin, switch_state, app_signal);  
        
    }

    return 0;
}
