#include "temp.h"
#include "adc.h"
#include "DIO.h"

static float alarm_threshold = 30  ;

void temp_init(void) {
    adc_init();                              // Initialize ADC module
    dio_init(PORT_E , PIN1 , OUT, DIGITAL); 
    dio_init(PORT_E , PHYSICAL_ALARM_PIN, OUT, DIGITAL); // Configure physical alarm pin
    dio_writepin(PORT_E , PHYSICAL_ALARM_PIN, 0);        // Ensure alarm is off initially
}

float temp_get_reading(void) {
    uint16_t adc_value = adc_read();
    // Convert ADC value to temperature (example: assume 0-1023 maps to 0-100°C)
    float temperature = (adc_value * 3300 / 4096);
    return temperature;
}

void temp_set_alarm_threshold(float threshold) {
    alarm_threshold = threshold;
}

void temp_check_alarm(void) {
    float current_temp = temp_get_reading();
    if (current_temp > alarm_threshold ) {  ///////////////////////////////"dio_readpin(uint8_t port, uint8_t pin);"
        temp_alarm_handler(); //Buzzer on               
        // Optional: Software alarm (e.g., send a message or blink LED)
    } else {
        dio_writepin(PORT_E, PHYSICAL_ALARM_PIN, 0); // Turn off physical alarm
    }
}

void temp_alarm_handler(void) {
    dio_writepin(PORT_E, PHYSICAL_ALARM_PIN, 1); // Turn on physical alarm
}
