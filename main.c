#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "DIO.h"
#include "bluetooth_module.h"
#include "magnetic_switch.h"
#include "temp.h"
#include "lamp_plug.h"



uint8_t mag_port = PORT_B;
uint8_t mag_pin = PIN4;


uint8_t previous_magnetic_switch_state = 0xFF;

void magnetic_switch_callback(void){
  uint8_t current_magnetic_switch_state = get_magnetic_switch_state(mag_port, mag_pin);
  if(current_magnetic_switch_state == previous_magnetic_switch_state ) return;
  if(current_magnetic_switch_state  == 1){
        Bluetooth_SendData("o");
        dio_writepin(PORT_F, 1, 0);
        dio_writepin(PORT_F, 2, 1);
        dio_writepin(PORT_F, 3, 1);
  }
  else{
        Bluetooth_SendData("c");
        dio_writepin(PORT_F, 1, 1);
        dio_writepin(PORT_F, 2, 0);
        dio_writepin(PORT_F, 3, 0);
  }
  
  previous_magnetic_switch_state = current_magnetic_switch_state;
}

void systick_callback(void){
    uint16_t temperature = temp_check_alarm();
    
    char str[10];  
    sprintf(str, "t%d", temperature);     // Convert integer to string
  
    Bluetooth_SendData((uint8_t*)str);
    

}

//uint8_t current_lamp_switch_state2 = 0;
//uint8_t current_plug_switch_state = 0;

/*
uint8_t lamp_port = PORT_F; 
uint8_t lamp_pin = 2; 
uint8_t plug_port = PORT_F; 
uint8_t plug_pin = 3; 
*/


/*
void bluetooth_callback(void){
    uint8_t received_string[MAX_WORD_LENGTH]; 
    Bluetooth_ReceiveData(received_string, MAX_WORD_LENGTH);
    
    if(received_string[0] == 'h') {  
        uint16_t threshold = atoi((char*)&received_string[1]);  // Skip the 'h' by using &received_string[1]
        temp_set_alarm_threshold(threshold);
        if (threshold == 3)
          dio_writepin(PORT_F, 1, 1); 
        else if(threshold == 23)
          dio_writepin(PORT_F, 2, 1); 
        else
          dio_writepin(PORT_F, 3, 1); 
    } 
    else if(received_string[0] == 's') { 
      if(received_string[1] == 'l') { 
        if(received_string[2] == '1') 
          set_app_lamp_switch_state(SWITCH_ON);
        else if(received_string[2] == '0') 
          set_app_lamp_switch_state(SWITCH_OFF); 
         lamp_update_state(lamp_port, lamp_pin, current_lamp_switch_state2);
      }
      else if(received_string[1] == 'p') { 
        if(received_string[2] == '1') 
          set_app_plug_switch_state(SWITCH_ON);
        else if(received_string[2] == '0') 
          set_app_plug_switch_state(SWITCH_OFF); 
         plug_update_state(plug_port, plug_pin, current_plug_switch_state);
      }
      
    }
}
*/


void callback(void){
        uint8_t received_string[MAX_WORD_LENGTH]; 
        Bluetooth_ReceiveData(received_string, MAX_WORD_LENGTH);
        if(received_string[0] == 'r') 
            dio_writepin(PORT_F, 1, 1);
            dio_writepin(PORT_F, 3, 1);
      
}



int main()
{      


    // initializing bluetooth module
    Bluetooth_Init(callback); 

    // initializing systick
    SysTickInit(16000000, systick_callback);
    
    // initializing magnetic switch module
    magnetic_switch_init(mag_port, mag_pin, magnetic_switch_callback);
    
    // initializing temperature sensor and buzzer
    uint16_t threshold = 0;
    uint8_t temp_port = PORT_E;
    uint8_t temp_pin = PIN3;
    uint8_t buzzer_port = PORT_E;
    uint8_t buzzer_pin = PIN5;
    temp_init(temp_port, temp_pin, threshold);
    buzzer_init( buzzer_port, buzzer_pin);
    
 
    
    // initializing lamp 
    uint8_t lamp_port = PORT_C; 
    uint8_t lamp_pin = 6; 
    lamp_init(lamp_port, lamp_pin);
    
    
    // initializing plug
    uint8_t plug_port = PORT_C; 
    uint8_t plug_pin = 4; 
    plug_init(plug_port, plug_pin);
    
 
    
    
//    c4 - lamp
//d7 - plug
//
//A2
//A3


    
    // initializing switches
    
    uint8_t switch_lamp_port = PORT_D; 
    uint8_t switch_lamp_pin = 7; 
    switch_init(switch_lamp_port, switch_lamp_pin);
    
    uint8_t switch_plug_port = PORT_A; 
    uint8_t switch_plug_pin = 3; 
    switch_init(switch_plug_port, switch_plug_pin);





    // uint8_t switch_state, app_signal, switch_plug_state, app_signal2;
     
    
    
    
    
    
// check initial values on ports 
    
    if(get_magnetic_switch_state(mag_port, mag_pin))
        Bluetooth_SendData("io");
    else
        Bluetooth_SendData("ic");
    
    
    
    
    
    
    
        
    dio_init(PORT_F, 3, OUT, DIGITAL);
    dio_init(PORT_F, 2, OUT, DIGITAL);    
    dio_init(PORT_F, 1, OUT, DIGITAL);

    
    dio_writepin(PORT_F, 1, 0);
    dio_writepin(PORT_F, 2, 0);
    dio_writepin(PORT_F, 3, 0);
     
    
    
    
    
    uint8_t received_string[MAX_WORD_LENGTH]; 
    
    
    
    uint8_t current_lamp_switch_state = SWITCH_OFF;
    uint8_t current_plug_switch_state = SWITCH_OFF;
    
    
    
    uint8_t previous_lamp_state = current_lamp_switch_state;
    uint8_t previous_plug_state = current_plug_switch_state;
    
    
    while(1) {
    
        current_lamp_switch_state = switch_get(switch_lamp_port, switch_lamp_pin);
        current_plug_switch_state = switch_get(switch_plug_port, switch_plug_pin);
         
        
        
        if(current_lamp_switch_state != previous_lamp_state){
            lamp_update_state(lamp_port, lamp_pin, current_lamp_switch_state);
            previous_lamp_state= current_lamp_switch_state;
        }
        if(current_plug_switch_state != previous_plug_state){
            plug_update_state(plug_port, plug_pin, current_plug_switch_state);
            previous_plug_state= current_plug_switch_state;
        }
          
        
        if(GET_BIT(UART0_FR_R, UART_FR_RXFE) == 0){
        
            uint8_t c = Bluetooth_ReceiveChar();
            if(c=='a'){
                set_app_lamp_switch_state(SWITCH_ON);
                lamp_update_state(lamp_port, lamp_pin, current_lamp_switch_state);    
            }
            else if(c=='b'){
                set_app_lamp_switch_state(SWITCH_OFF);
                lamp_update_state(lamp_port, lamp_pin, current_lamp_switch_state); 
            }   
            else if(c=='c'){
                set_app_plug_switch_state(SWITCH_ON);
                plug_update_state(plug_port, plug_pin, current_plug_switch_state);
            }
            else if(c=='d'){
                set_app_plug_switch_state(SWITCH_OFF); 
                plug_update_state(plug_port, plug_pin, current_plug_switch_state);
            }
        }
    
    }
    
}  
    
    
    
    

       //bluetooth_callback();

      //  memset(received_string, 0, MAX_WORD_LENGTH);
   // if(GET_BIT(UART0_FR_R, UART_FR_RXFE) == 0){
/*
            Bluetooth_ReceiveData(received_string, MAX_WORD_LENGTH);
        
            if(received_string[0] == 's') { 
                  if(received_string[1] == 'l') { 
                    if(received_string[2] == '1') 
                      set_app_lamp_switch_state(SWITCH_ON);
                    else if(received_string[2] == '0') 
                      set_app_lamp_switch_state(SWITCH_OFF); 
                     lamp_update_state(lamp_port, lamp_pin, current_lamp_switch_state);
                  }
                  else if(received_string[1] == 'p') { 
                    if(received_string[2] == '1') 
                      set_app_plug_switch_state(SWITCH_ON);
                    else if(received_string[2] == '0') 
                      set_app_plug_switch_state(SWITCH_OFF); 
                     plug_update_state(plug_port, plug_pin, current_plug_switch_state);
                  }
                  
                  
            }
            
            

  //  }
      
      
//        Bluetooth_ReceiveData(received_string, MAX_WORD_LENGTH);
//        
//        if(received_string[0] == 'h') {  
//            uint16_t threshold = atoi((char*)&received_string[1]);  // Skip the 'h' by using &received_string[1]
//            temp_set_alarm_threshold(threshold);
//            if (threshold == 3)
//              dio_writepin(PORT_F, 1, 1); 
//            else if(threshold == 23)
//              dio_writepin(PORT_F, 2, 1); 
//            else
//              dio_writepin(PORT_F, 3, 1); 
//        }
          
    }*/

       
//}






