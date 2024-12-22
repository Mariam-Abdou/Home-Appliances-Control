#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "DIO.h"
#include "bluetooth_module.h"
#include "magnetic_switch.h"
#include "temp.h"


uint8_t mag_port = PORT_B;
uint8_t mag_pin = PIN4;


uint8_t previous_magnetic_switch_state = 0xFF;

void magnetic_switch_callback(void){
  uint8_t current_magnetic_switch_state = get_magnetic_switch_state(PORT_B, 4);
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
}



void callback(void){
    dio_writepin(PORT_F, 1, 1);
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
    uint16_t threshold = 40;
    uint8_t temp_port = PORT_E;
    uint8_t temp_pin = PIN3;
    uint8_t buzzer_port = PORT_E;
    uint8_t buzzer_pin = PIN5;
    temp_init(temp_port, temp_pin, buzzer_port, buzzer_pin, threshold);

    
 

        
    dio_init(PORT_F, 3, OUT, DIGITAL);
    dio_init(PORT_F, 2, OUT, DIGITAL);    
    dio_init(PORT_F, 1, OUT, DIGITAL);

    
    dio_writepin(PORT_F, 1, 0);
    dio_writepin(PORT_F, 2, 0);
    dio_writepin(PORT_F, 3, 0);
     

    
    uint8_t received_string[MAX_WORD_LENGTH];          
    while(1) {

        Bluetooth_ReceiveData(received_string, MAX_WORD_LENGTH);
        if(received_string[0] == 'h')
              dio_writepin(PORT_F, 2, 1);
          
    }

       
}







