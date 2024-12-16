#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"


// Define the pins
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7





#define UART0 0     // Bit to enable clock for UART0
#define PORTA 0     // Bit to enable clock for GPIO Port A

#define UART_CTL_EN 0
#define UART_CTL_TXINTEN 8   //transmit interrupt
#define UART_CTL_RXINTEN 9   //receive interrupt


#define UART0_BAUD_INT 104          // Integer part for 9600 baud
#define UART0_BAUD_FRAC 11          // Fractional part for 9600 baud


#define UART_CC_SYS_CLOCK 0x0            // Use system clock
#define UART_LCRH_WLEN_8 (0x3 << 5)  // 8-bit word length 

#define UART_LCRH_STOP_BIT 4        
#define UART_LCRH_PARITY 3         


// UART0 Interrupt Mask Register (IM) Defines
#define UART0_IM_R_RXIM 4  // RX interrupt
#define UART0_IM_R_TXIM 5  //  TX interrupt

// NVIC Interrupt Enable Register 0 (EN0) 
#define NVIC_EN0_R_UART0 5  // Enable IRQ5 for UART0 interrupt


#define UART0_MIS_R_RXMIS 4  // RX interrupt occurred
#define UART0_MIS_R_TXMIS 5  // TX interrupt occurred

#define UART0_FR_R_RXFF 4  // RX FIFO full
#define UART0_FR_R_TXFF 5  // TX FIFO full

#define UART0_ICR_R_RXIC 4  // RX interrupt clear
#define UART0_ICR_R_TXIC 5  // TX interrupt clear



////////////////////////////////////
// UART Control Register (CTL)
#define UART_CTL_UARTEN             (1 << 0) // UART Enable
#define UART_CTL_TXE                (1 << 8) // Transmit Enable
#define UART_CTL_RXE                (1 << 9) // Receive Enable

// UART Interrupt Mask Register (IM)
#define UART_IM_RXIM                (1 << 4) // RX Interrupt Mask

// UART Interrupt Clear Register (ICR)
#define UART_ICR_RXIC               (1 << 4) // RX Interrupt Clear

// UART Line Control Register (LCRH)
#define UART_LCRH_WLEN_8            (0x3 << 5) // 8-bit word length

// UART Clock Configuration (CC)
#define UART_CC_SYSTEM_CLOCK        0x0 // Use system clock


// UART Flags Register (FR)
#define UART_FR_TXFF                (1 << 5) // Transmit FIFO Full

// GPIO Alternate Function Select (AFSEL)
#define GPIO_AFSEL_PIN0             (1 << 0) // Enable alternate function for PA0
#define GPIO_AFSEL_PIN1             (1 << 1) // Enable alternate function for PA1

// GPIO Port Control (PCTL)
#define GPIO_PCTL_PA0_UART0_RX      (1 << 0) // PA0 as UART0 RX
#define GPIO_PCTL_PA1_UART0_TX      (1 << 4) // PA1 as UART0 TX

// GPIO Digital Enable (DEN)
#define GPIO_DEN_PIN0               (1 << 0) // Enable digital function for PA0
#define GPIO_DEN_PIN1               (1 << 1) // Enable digital function for PA1

// GPIO Analog Mode Select (AMSEL)
#define GPIO_AMSEL_DISABLE_PIN0     ~(1 << 0) // Disable analog function for PA0
#define GPIO_AMSEL_DISABLE_PIN1     ~(1 << 1) // Disable analog function for PA1

// NVIC Interrupt Enable
#define NVIC_EN0_UART0              (1 << 5) // Enable UART0 interrupt

// Baud Rate Divisors for 16 MHz clock and 9600 baud rate
#define UART_IBRD_9600              104  // Integer Baud-Rate Divisor
#define UART_FBRD_9600              11   // Fractional Baud-Rate Divisor



// Function Prototypes
void UART0_Init(void (*callback)(void));
void UART0_TransmitChar(char c);
void UART0_TransmitString(const char *str);
void GPIO_Init(void);
void UART0_Handler(void);




#endif