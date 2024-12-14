#include "magnetic_switch2.h"



static void (*interrupt_callback)(void) = 0;  // Pointer to the interrupt callback function

uint8_t magnetic_switch_init(char port){
    int pin = 3;
    dio_init('D', pin, INPUT, PULL_DOWN, DIGITAL);

   

    // Configure GPIO interrupt settings
    CLEAR_BIT(GPIO_PORTD_IM_R, pin);  // Disable interrupt for the pin
    SET_BIT(GPIO_PORTD_IS_R, pin);    // Edge-sensitive interrupt
    SET_BIT(GPIO_PORTD_IBE_R, pin);   // Interrupt on both edges
    SET_BIT(GPIO_PORTD_ICR_R, pin);   // Clear any prior interrupts
    SET_BIT(GPIO_PORTD_IM_R, pin);    // Enable interrupt for the pin

    NVIC_EN0_R |= (1 << 30);  // Enable IRQ30 for Port F in NVIC

    
}



uint8_t magnetic_switch_get_state(uint8_t pin){
    return dio_readpin('D', pin);  
}



// Interrupt service routine for GPIO Port F (Pin 3)
void magnetic_switch_handler(uint8_t pin) {    /////####################
    if (GET_BIT(GPIO_PORTD_RIS_R,pin)) {  // Check if interrupt was triggered on PIN3
        CLEAR_BIT(GPIO_PORTD_ICR_R, pin);  // Clear the interrupt flag
        
        // If callback is set, call it
        if (interrupt_callback != 0) {
            interrupt_callback();  // Call the user-defined callback function
        }
    }
}

