#include "temp.h"
#include "DIO.h"
#include <stdint.h>


void temperature_callback(void){
    temp_check_alarm();
}

       
int main()
{      
       uint8_t threshold = 200;
       temp_init(PORT_E, PIN1, PORT_E, PIN5, threshold, temperature_callback);
       dio_init(PORT_F, 0, IN, DIGITAL);
       dio_pull(PORT_F, 0, UP);
       
       
       dio_init(PORT_F, 1, OUT, DIGITAL);
       dio_init(PORT_F, 2, OUT, DIGITAL);
                  dio_writepin(PORT_F, 1, 0); //red
                  dio_writepin(PORT_F, 2, 0); //red
                  dio_writepin(PORT_F, 3, 0); //red
       
                  
      // dio_writepin(PORT_E, PHYSICAL_ALARM_PIN, 0);
       while(1){ 
         


       
       }
       
  return 0;
}