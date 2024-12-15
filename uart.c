#include "uart.h"



// Global Variables
volatile char received_char = 0;
static void (*interrupt_callback)(void) = 0;  // Pointer to the interrupt callback function



void UART0_Init(void (*callback)(void)) {


    SET_BIT(SYSCTL_RCGCGPIO_R, PORT_A);   // Enable clock for GPIOA  

    while ((GET_BIT(SYSCTL_PRGPIO_R, PORT_A) == 0)); // Wait for the port to be ready 

    SET_BIT(GPIO_PORTA_AFSEL_R, PIN0); // Enable alternate functions for PA0 
    SET_BIT(GPIO_PORTA_AFSEL_R, PIN1); // Enable alternate functions for PA1

    GPIO_PORTA_PCTL_R &= ~0xFF; // Clear PCTL bits //todo
    GPIO_PORTA_PCTL_R |= (1 << 0) | (1 << 4); //todo


    SET_BIT(GPIO_PORTA_DEN_R, PIN0); // Enable digital function for PA0
    SET_BIT(GPIO_PORTA_DEN_R, PIN1); // Enable digital function for PA1

    GPIO_PORTA_AMSEL_R &= ~((1 << 0) | (1 << 1)); // Disable analog function //? redundant
    



    SET_BIT(SYSCTL_RCGCUART_R, UART0);   // Enable clock for UART0 
    while ((GET_BIT(SYSCTL_PRUART_R, UART0) == 0));    // Wait for the port to be ready 

    CLEAR_BIT(UART0_CTL_R, UART_CTL_EN);
    UART0_IBRD_R = UART0_BAUD_INT;                  // Integer part of baud rate value
    UART0_FBRD_R = UART0_BAUD_FRAC;                 // Fractional part of baud rate value

    UART0_LCRH_R = UART_LCRH_WLEN_8;                // 8-bit word length
    SET_BIT(UART0_LCRH_R, UART_LCRH_FIFO);           // enbale FIFO
    CLEAR_BIT(UART0_LCRH_R, UART_LCRH_STOP_BIT);    // 1 stop bit
    CLEAR_BIT(UART0_LCRH_R, UART_LCRH_PARITY);      // No parity

    UART0_CC_R = UART_CC_SYS_CLOCK;                 // Use system clock
    SET_BIT(UART0_IM_R, UART_IM_RXIM);              // Enable RX interrupt
    SET_BIT(NVIC_EN0_R, NVIC_EN0_R_UART0);          // Enable IRQ5 for UART0 in NVIC //!
    
    SET_BIT(UART0_CTL_R, UART_CTL_EN);
    SET_BIT(UART0_CTL_R, UART_CTL_TXEN);
    SET_BIT(UART0_CTL_R, UART_CTL_RXEN);

    interrupt_callback = callback;

}


void UART0_TransmitChar(char c) {
    while (GET_BIT(UART0_FR_R, UART_FR_TXFF)); // Wait until the transmit FIFO is not full
    UART0_DR_R = c; // Write the character to the data register
}
 
void UART0_TransmitString(const char *str) {
    while (*str) {
        UART0_TransmitChar(*str++);
    }
}

void UART0_Handler(void) {
    if (interrupt_callback != 0) {
        interrupt_callback();  // Call the user-defined callback function
    }

}