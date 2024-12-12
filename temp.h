#ifndef TEMP_H
#define TEMP_H

#include "DIO.h"
#include "types.h"

#define LM35_PIN 3  // PE3 for AIN0 (ADC0 channel 0)

/* Function prototypes */
void buzzer_init(void);
void ADC_init(void);
void buzzer_on(void);
void buzzer_off(void);
uint32 read_temp(void);  

#endif /* TEMP_H */
