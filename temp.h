#ifndef TEMP_H
#define TEMP_H

#include <stdint.h>


// Function Prototypes
void temp_init(uint8_t port, uint8_t pin, uint8_t port_buzz, uint8_t pin_buzz, uint16_t threshold);                     // Initialize the temperature module
uint16_t temp_get_reading(void);             // Get the current temperature in °C
uint16_t temp_check_alarm(void);              // Check and trigger alarm if needed
void temp_set_alarm_threshold(uint16_t);     // Set the temperature alarm threshold
void on_buzzer(void);                        // Turn on the buzzer
void off_buzzer(void);                       // Turn off the buzzer
#endif // TEMP_H

