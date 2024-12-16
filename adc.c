#include "adc.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "DIO.h"

void adc_init(uint8_t adc_pin) {
    // Enable ADC0 and the required GPIO port
    SET_BIT(SYSCTL_RCGCADC_R, adc_pin);
    dio_init(PORT_E, adc_pin , IN, ANALOG );

    CLEAR_BIT(ADC0_ACTSS_R, 3);             // Disable sample sequencer 3
    // Software trigger for sequencer 3
    CLEAR_BIT(ADC0_EMUX_R, 12);
    CLEAR_BIT(ADC0_EMUX_R, 13);
    CLEAR_BIT(ADC0_EMUX_R, 14);  
    CLEAR_BIT(ADC0_EMUX_R, 15);

    
    // Configure ADC0
    ADC0_ACTSS_R &= ~8;                    // Disable sample sequencer 3
    ADC0_EMUX_R &= ~0xF000;                // Software trigger for sequencer 3
    ADC0_SSMUX3_R = 0;                     // Select AIN0 (PE3)
    ADC0_SSCTL3_R = 0x6;                   // End of sequence and enable interrupt
    ADC0_ACTSS_R |= 8;                     // Enable sample sequencer 3
}

uint16_t adc_read() {
    ADC0_PSSI_R = 8;                       // Start sampling on sequencer 3
    while ((ADC0_RIS_R & 8) == 0);         // Wait for conversion to complete
    uint16_t result = ADC0_SSFIFO3_R & 0xFFF; // Read 12-bit result
    ADC0_ISC_R = 8;                        // Clear completion flag
    return result;
}
