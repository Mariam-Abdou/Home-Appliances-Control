#include "Systick.h"
#include "utils.h"
#include "tm4c123gh6pm.h"

// Pointer to the SysTick callback function
static void (*SysTickCallback)(void) = 0;

// Initialize SysTickS Timer
void SysTickInit(uint32_t period, void (*callback)(void)) {
	SysTickDisable();					// Disable SysTick during setup
	SysTickPeriodSet(period);			// Set the reload value
    SysTickCurrentSet(0);				// Reset the counter
	SysTickEnable();					// Enable timer

	SysTickInterruptEnable();			// Enable interrupt
    SysTickCallback = callback;			// Register the callback function
}

// Enable SysTick Timer
void SysTickEnable(void) {
    SET_BIT(NVIC_ST_CTRL_R, SYSTICK_ENABLE);
    SET_BIT(NVIC_ST_CTRL_R, SYSTICK_CLK_SOURCE);
}

// Disable SysTick Timer
void SysTickDisable(void) {
    CLEAR_BIT(NVIC_ST_CTRL_R, SYSTICK_ENABLE);
}

// Enable SysTick Interrupt
void SysTickInterruptEnable(void) {
    SET_BIT(NVIC_ST_CTRL_R, SYSTICK_INTERRUPT);	
}

// Set the SysTick Timer period
void SysTickPeriodSet(uint32_t period) {
    NVIC_ST_RELOAD_R = period - 1; 
}

// Get the SysTick Timer period
uint32_t SysTickPeriodGet(void) {
    return NVIC_ST_RELOAD_R + 1;      
}

// Set the current value of the SysTick Timer
void SysTickCurrentSet(uint32_t value) {
    NVIC_ST_CURRENT_R = value;         
}

// Get the current value of the SysTick Timer
uint32_t SysTickCurrentGet(void) {
    return NVIC_ST_CURRENT_R;         
}

// Check if SysTick Timer has timed out
uint8_t SysTickIsTimeout(void) {
    return GET_BIT(NVIC_ST_CTRL_R, SYSTICK_COUNT_FLAG);
}

// SysTick Interrupt Handler
void SysTickHandler(void) {
    if (SysTickCallback != 0)
        SysTickCallback();				// Call the user-defined handler function
}



