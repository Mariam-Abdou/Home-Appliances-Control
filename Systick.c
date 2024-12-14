#include "Systick.h"

//D16           D2     D1   D0
//countFlag clksource inter enable

// Pointer to the SysTick callback function
static void (*SysTick_Callback)(void) = 0;

// Initialize SysTick Timer
void SysTick_Init(uint32_t reloadValue) {
    NVIC_ST_CTRL_R = 0;               // Disable SysTick during setup
    NVIC_ST_RELOAD_R = reloadValue;   // Set reload value
    NVIC_ST_CURRENT_R = 0;            // Clear current timer value
    SET_BIT(NVIC_ST_CTRL_R, SYSTICK_ENABLE);
    SET_BIT(NVIC_ST_CTRL_R, SYSTICK_CLK_SOURCE);
}

// Initialize SysTick Timer (interrupt mode)
void SysTick_InitInterrupt(uint32_t reloadValue, void (*callback)(void)) {
    SysTick_Init(reloadValue);
    SysTick_Callback = callback;      // Register the callback function
    SET_BIT(NVIC_ST_CTRL_R, SYSTICK_INTERRUPT);
}

// Enable SysTick Timer
void SysTick_Enable(void) {
    SET_BIT(NVIC_ST_CTRL_R, SYSTICK_ENABLE);
    SET_BIT(NVIC_ST_CTRL_R, SYSTICK_CLK_SOURCE);
}

// Disable SysTick Timer
void SysTick_Disable(void) {
    CLEAR_BIT(NVIC_ST_CTRL_R, SYSTICK_ENABLE);
}

// Set the SysTick Timer period
void SysTick_PeriodSet(uint32_t ui32Period) {
    NVIC_ST_RELOAD_R = ui32Period - 1; 
}

// Get the SysTick Timer period
uint32_t SysTick_PeriodGet(void) {
    return NVIC_ST_RELOAD_R + 1;      
}

// Get the current value of the SysTick Timer
uint32_t SysTick_ValueGet(void) {
    return NVIC_ST_CURRENT_R;         
}

// Check if SysTick Timer has timed out
bool SysTick_Is_Time_Out(void) {
    return GET_BIT(NVIC_ST_CTRL_R, SYSTICK_COUNT_FLAG);
}


// SysTick Interrupt Handler
void SysTick_Handler(void) {
    if (SysTick_Callback != 0) {
        SysTick_Callback();           // Call the user-defined callback function
    }
}



