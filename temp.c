#include "temp.h"

#define LM35_PIN 3  // PE3 for AIN0 (ADC0 channel 0)
uint32 temperature;

void buzzer_init(port, pin) {
    dio_init(port, pin, OUTPUT, 0, 1);  // Configure Port Pin as a digital output
}

void ADC_init(port, pin){	
	dio_init(port, pin, INPUT, 0, DIGITAL);		// enable clock, unlock, direction, pull, digital

    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~8;             /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;         /* software trigger conversion */ 
    ADC0_SSMUX3_R = 0;              /* get input from channel 0 (PE3) */
    ADC0_SSCTL3_R |= 6;             /* take one sample at a time, set flag at 1st sample */
    ADC0_ACTSS_R |= 8;              /* enable ADC0 sequencer 3 */
}

void buzzer_on(port, pin) {
    dio_writepin(port, pin, 1);  // Set PB1 HIGH to turn ON the buzzer
}

void buzzer_off(port, pin) {
    dio_writepin(port, pin, 0);  // Set PB1 LOW to turn OFF the buzzer
}

uint32 read_temp(port, pin){			//buzzer pin 
    ADC0_PSSI_R |= 8;           // start a conversion sequence 3 
    while((ADC0_RIS_R & 0x08) == 0);                       /* wait for conversion to complete */
    temperature = ((ADC0_SSFIFO3_R * 3300) / 4096);  // Convert ADC value to temperature in Fahrenheit
    if ((temperature > 30) && (dio_readpin(port, pin) == 0)) {
      buzzer_on();
    } else if ((temperature <= 30) && (dio_readpin(port, pin) == 1)) {
      buzzer_off();
    }
    ADC0_ISC_R = 8;             /* clear completion flag  */
    return temperature;
}
