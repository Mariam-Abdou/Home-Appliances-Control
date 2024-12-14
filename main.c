#include "magnetic_switch.h"

// Example main loop to demonstrate usage
int main(void) {

    dio_init(PORT_F, 3, OUT, DIGITAL);
    dio_init(PORT_F, 2, OUT, DIGITAL);    
    dio_init(PORT_F, 1, OUT, DIGITAL);

    magnetic_switch_init(PORT_B, 0);
     
    uint8_t current_door_state, previous_door_state;
    current_door_state = get_magnetic_switch_state(PORT_B, 0);

    while (1) {
      previous_door_state = current_door_state;     
      current_door_state = get_magnetic_switch_state(PORT_B, 0);
      
      if (previous_door_state != current_door_state) {
          dio_writepin(PORT_F, 3, 0);
          dio_writepin(PORT_F, 2, 0);
          dio_writepin(PORT_F, 1, 0);
            
          if (current_door_state == OPEN)          // OPEN
                dio_writepin(PORT_F, 3, 1);
          else if (current_door_state == CLOSED)     // CLOSED
                dio_writepin(PORT_F, 2, 1);
          else  dio_writepin(PORT_F, 1, 1);
      }
    }

}