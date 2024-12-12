#include "DIO.h"
#include "types.h"
#include "temp.h"

#define LM35_PIN 3  // PE3 for AIN0 (ADC0 channel 0)
uint32 temperature;

void ADC_init(){
    SYSCTL_RCGCGPIO_R |= 0x10;      /* enable clock to GPIO_PORTE */
    SYSCTL_RCGCADC_R |= 1;          /* enable clock to ADC0 */
    dio_init('E', LM35_PIN, INPUT, 0, 0);  /* Configure PE3 for analog input */
    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~8;             /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;         /* software trigger conversion */ 
    ADC0_SSMUX3_R = 0;              /* get input from channel 0 (PE3) */
    ADC0_SSCTL3_R |= 6;             /* take one sample at a time, set flag at 1st sample */
    ADC0_ACTSS_R |= 8;              /* enable ADC0 sequencer 3 */
}
uint32 read_temp(){
    ADC_init();
    ADC0_PSSI_R |= 8;           /* start a conversion sequence 3 */
    while((ADC0_RIS_R & 0x08) == 0);                       /* wait for conversion to complete */
    temperature = ((ADC0_SSFIFO3_R * 330) / 4096);  // Convert ADC value to temperature in Fahrenheit
    ADC0_ISC_R = 8;             /* clear completion flag  */
    return temperature;
}
