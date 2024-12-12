#include "magnetic_switch.h"
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"

static void (*interrupt_callback)(void) = 0;  // Pointer to the interrupt callback function

uint8_t magnetic_switch_init(char port, uint8_t pin, void (*callback)(void)){

    dio_init('F', pin, INPUT, PULL_DOWN, DIGITAL);

   

    // Configure GPIO interrupt settings
    CLEAR_BIT(GPIO_PORTF_IM_R, pin);  // Disable interrupt for the pin
    SET_BIT(GPIO_PORTF_IS_R, pin);    // Edge-sensitive interrupt
    SET_BIT(GPIO_PORTF_IBE_R, pin);   // Interrupt on both edges
    SET_BIT(GPIO_PORTF_ICR_R, pin);   // Clear any prior interrupts
    SET_BIT(GPIO_PORTF_IM_R, pin);    // Enable interrupt for the pin

    NVIC_EN0_R |= (1 << 30);  // Enable IRQ30 for Port F in NVIC

    interrupt_callback = callback;
    
}



uint8_t magnetic_switch_get_state(uint8_t pin){
    return dio_readpin('F', pin);  
}



// Interrupt service routine for GPIO Port F (Pin 3)
void magnetic_switch_handler(uint8_t pin) {    /////####################
    if (GET_BIT(GPIO_PORTF_RIS_R,pin)) {  // Check if interrupt was triggered on PIN3
        CLEAR_BIT(GPIO_PORTF_ICR_R, pin);  // Clear the interrupt flag
        
        // If callback is set, call it
        if (interrupt_callback != 0) {
            interrupt_callback();  // Call the user-defined callback function
        }
    }
}

