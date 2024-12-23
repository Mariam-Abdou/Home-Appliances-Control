#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "utils.h"


#define MAX_WORD_LENGTH 16

#define UART0 0    

#define PORT_A 0 

#define PIN0 0
#define PIN1 1


// GPIO Port Control (PCTL)
#define GPIO_PCTL_PA0_UART0      0 // PA0 as UART0 RX
#define GPIO_PCTL_PA1_UART0      4 // PA1 as UART0 TX



// UART Control Register (CTL)
#define UART_CTL_EN 0                      // UART Enable
#define UART_CTL_TXEN 8                         // Transmit Enable
#define UART_CTL_RXEN 9                         // Receive Enable


// setting Baud Rate
#define UART0_BAUD_INT 104          // Integer part for 9600 baud
#define UART0_BAUD_FRAC 11          // Fractional part for 9600 baud

// Line Control Register High (LCRH)
#define UART_LCRH_WLEN_5 (0x0 << 5)  // 5-bit word length 
#define UART_LCRH_WLEN_6 (0x1 << 5)  // 6-bit word length 
#define UART_LCRH_WLEN_7 (0x2 << 5)  // 7-bit word length 
#define UART_LCRH_WLEN_8 (0x3 << 5)  // 8-bit word length 
#define UART_LCRH_FIFO 4             // FIFO
#define UART_LCRH_STOP_BIT 3         // stop bit 
#define UART_LCRH_PARITY 1           // Parity enable

// NVIC Interrupt Enable Register 0 (EN0) 
#define NVIC_EN0_R_UART0 5  // Enable IRQ5 for UART0 interrupt

// UART0 Interrupt Mask Register (IM)
#define UART0_IM_R_RXIM 4  // RX interrupt
#define UART0_IM_R_TXIM 5  //  TX interrupt

// UART0 Masked Interrupt Status Register (MIS)
#define UART0_MIS_R_RXMIS 4  // RX interrupt occurred
#define UART0_MIS_R_TXMIS 5  // TX interrupt occurred

// UART0 Flag Register (FR)
#define UART_FR_BUSY 3        // UART Busy Transmitting
#define UART_FR_RXFE 4        // Receive FIFO Empty
#define UART_FR_TXFF 5        // Transmit FIFO Full
#define UART_FR_RXFF 6        // Receive FIFO Full
#define UART_FR_TXFE 7        // Transmit FIFO Empty

// UART0 Interrupt Clear Register (ICR)
#define UART0_ICR_R_RXIC 4  // RX interrupt clear
#define UART0_ICR_R_TXIC 5  // TX interrupt clear


// RIS
#define UART_RIS_RXRIS 4    // Receive Raw Interrupt Status
#define UART_RIS_TXRIS 5    // Transmit Raw Interrupt Status

#define UART_CC_SYS_CLOCK 0x0            // Use system clock



// Function Prototypes
void UART0_Init();
void UART0_TransmitChar(uint8_t c);
void UART0_TransmitString(const uint8_t *str);
uint8_t UART0_ReceiveChar(void);
void UART0_ReceiveString(uint8_t *str, uint32_t max_length);
void GPIO_Init(void);





#endif

