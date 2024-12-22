#ifndef ADC_H
#define ADC_H

#include <stdint.h>



// Function Prototypes
void adc_init(uint8_t adc_pin);                // Initialize ADC module
uint16_t adc_read();                // Read ADC value from the specified channel

#endif // ADC_H
