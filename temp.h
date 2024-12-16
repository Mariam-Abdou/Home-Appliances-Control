#ifndef TEMP_H
#define TEMP_H

#include <stdint.h>


#define PHYSICAL_ALARM_PIN PIN2    // Pin for the physical alarm

// Function Prototypes
void temp_init(void);                     // Initialize the temperature module
float temp_get_reading(void);             // Get the current temperature in °C
void temp_set_alarm_threshold(float);     // Set the temperature alarm threshold
void temp_check_alarm(void);              // Check and trigger alarm if needed
void temp_alarm_handler(void);            // Physical alarm control

#endif // TEMP_H
