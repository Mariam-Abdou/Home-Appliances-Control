#ifndef TEMP_H
#define TEMP_H

#include "DIO.h"
#include "types.h"

#define LM35_PIN 3  // PE3 for AIN0 (ADC0 channel 0)

/* Function prototypes */
void ADC_init(void);           // Initialize ADC and GPIO for LM35
int read_temp(void);           // Read the temperature in Celsius

#endif /* TEMP_H */
