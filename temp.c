#include "temp.h"
#include "adc.h"
#include "DIO.h"

static uint16_t alarm_threshold;
static void (*interrupt_callback)(void) = 0;	
static uint8_t port_buzzer, pin_buzzer;

void temp_init(uint8_t port, uint8_t pin, uint8_t port_buzz, uint8_t pin_buzz, uint16_t threshold, void (*callback)(void)) {
    adc_init(0);                              // Initialize ADC module
    dio_init(port, pin, OUT, DIGITAL); 
    
    port_buzzer = port_buzz;
    pin_buzzer = pin_buzz;
    
    
    dio_init(port_buzzer , pin_buzzer, OUT, DIGITAL); // Configure physical alarm pin
    dio_writepin(port_buzzer , pin_buzzer, 0);        // Ensure alarm is off initially
    
    alarm_threshold = threshold;
    
    interrupt_callback = callback;
}

uint16_t temp_get_reading(void) {
    uint16_t adc_value = adc_read();
    // Convert ADC value to temperature (example: assume 0-1023 maps to 0-100°C)
    
    
    uint16_t temperature = (adc_value * 3300 / 4096);

    
    return temperature;
}

//void temp_set_alarm_threshold(uint16_t threshold) {
//    alarm_threshold = threshold;
//}

void temp_check_alarm(void) {
    uint16_t current_temp = temp_get_reading();
    uint8_t buzzer_state = dio_readpin(port_buzzer, pin_buzzer);
    if (current_temp >= alarm_threshold) {  ///////////////////////////////"dio_readpin(uint8_t port, uint8_t pin);"
    dio_writepin(port_buzzer, pin_buzzer, 1);         
        // Optional: Software alarm (e.g., send a message or blink LED)
    } else {
    dio_writepin(port_buzzer, pin_buzzer, 0);
    }
}
//
//void on_buzzer(void){
//    dio_writepin(port_buzzer, pin_buzzer, 1);
//}
//                 
//void off_buzzer(void){
//    dio_writepin(port_buzzer, pin_buzzer, 0);
//}
//    


void temp_alarm_handler(void) {
  
    if (interrupt_callback  != 0)
        interrupt_callback();		// Call the user-defined callback function


  
}
