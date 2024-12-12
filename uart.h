#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"



// Function Prototypes
void UART0_Init(void);
void UART0_TransmitChar(char c);
void UART0_TransmitString(const char *str);
void GPIO_Init(void);
void UART0_Handler(void);




#endif