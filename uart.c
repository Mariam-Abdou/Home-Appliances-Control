#include "uart.h"





//static void (*interrupt_callback)(void) = 0;  

//volatile uint8_t received_char = 0;
//volatile uint8_t received_string[MAX_WORD_LENGTH] = {0};

void UART0_Init() {


    SET_BIT(SYSCTL_RCGCGPIO_R, PORT_A);   // Enable clock for GPIOA  

    while ((GET_BIT(SYSCTL_PRGPIO_R, PORT_A) == 0)); // Wait until port is ready

    SET_BIT(GPIO_PORTA_AFSEL_R, PIN0); // Enable alternate functions for PA0 
    SET_BIT(GPIO_PORTA_AFSEL_R, PIN1); // Enable alternate functions for PA1 

    GPIO_PORTA_PCTL_R &= ~0xFF; // Clear PCTL bits 
    SET_BIT(GPIO_PORTA_PCTL_R, GPIO_PCTL_PA0_UART0); // Configures PA0 as RX
    SET_BIT(GPIO_PORTA_PCTL_R, GPIO_PCTL_PA1_UART0); // Configures PA1 as TX
    


    SET_BIT(GPIO_PORTA_DEN_R, PIN0); // Enable digital function for PA0
    SET_BIT(GPIO_PORTA_DEN_R, PIN1); // Enable digital function for PA1

    CLEAR_BIT(GPIO_PORTA_AMSEL_R, PIN0); // Disable analog function for PA0
    CLEAR_BIT(GPIO_PORTA_AMSEL_R, PIN1); // Disable analog function for PA1

    



    SET_BIT(SYSCTL_RCGCUART_R, UART0);   // Enable clock for UART0 
    while ((GET_BIT(SYSCTL_PRUART_R, UART0) == 0));    // Wait for the port to be ready 

    CLEAR_BIT(UART0_CTL_R, UART_CTL_EN);
    UART0_IBRD_R = UART0_BAUD_INT;                  // Integer part of baud rate value
    UART0_FBRD_R = UART0_BAUD_FRAC;                 // Fractional part of baud rate value
    UART0_LCRH_R = UART_LCRH_WLEN_8;                // 8-bit word length
    SET_BIT(UART0_LCRH_R, UART_LCRH_FIFO);           // enable FIFO
    CLEAR_BIT(UART0_LCRH_R, UART_LCRH_STOP_BIT);    // 1 stop bit
    CLEAR_BIT(UART0_LCRH_R, UART_LCRH_PARITY);      // No parity
    UART0_CC_R = UART_CC_SYS_CLOCK;                 // Use system clock
    SET_BIT(UART0_IM_R, UART_IM_RXIM);              // Enable RX interrupt
    SET_BIT(NVIC_EN0_R, NVIC_EN0_R_UART0);          // Enable IRQ5 for UART0 in NVIC //!
    
    SET_BIT(UART0_CTL_R, UART_CTL_EN);
    SET_BIT(UART0_CTL_R, UART_CTL_TXEN);
    SET_BIT(UART0_CTL_R, UART_CTL_RXEN);

}


void UART0_TransmitChar(uint8_t c) {
    while (GET_BIT(UART0_FR_R, UART_FR_TXFF)); // Wait until the transmit FIFO is not full
    UART0_DR_R = c; // Write the character to the data register
}
 
void UART0_TransmitString(const uint8_t *str) {
    while (*str) {
        UART0_TransmitChar(*str++);
    }
}

uint8_t UART0_ReceiveChar(void) {
  while (GET_BIT(UART0_FR_R, UART_FR_RXFE) != 0);  // Wait until the receive FIFO is not empty
  return (uint8_t)(UART0_DR_R & 0xFF);  // Read and return the received character
}


/*

// Function to receive a complete word over UART
void UART0_ReceiveString(uint8_t* w) {
    uint8_t size = sizeof(w);


    uint8_t i = 0;
    uint8_t c = UART0_ReceiveChar();
    while(c != '\0' && i < size-1){
        w[i++] = c;
        c = UART0_ReceiveChar();
    }
    w[i] = '\0';
}
*/



/*
void UART0_Handler(void) {
    if (UART0_MIS_R & (1 << 4)) { // Check if RX interrupt occurred
        received_char = (uint8_t)(UART0_DR_R & 0xFF); // Read the received character
        
        UART0_TransmitChar(received_char);
        
        UART0_ICR_R |= (1 << 4); // Clear RX interrupt flag
    }
}
*/