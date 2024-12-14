#include "door2.h"
#include <stdio.h>

// Example main loop to demonstrate usage
int main(void) {
    door_init();
    dio_writepin('F', 3, 0);

    
    while (1) {
        door_check_state();
        
        // Small delay to prevent excessive checking
        // You might replace this with a more sophisticated timing method
         // Adjust delay as needed
    }
    
    return 0;
}