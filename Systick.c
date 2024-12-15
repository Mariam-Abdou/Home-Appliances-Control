#include "Systick.h"
#include "utils.h"

// Pointer to the SysTick callback function
static void (*SysTick_Callback)(void) = 0;

// Initialize SysTick Timer
void SysTickInit(uint32_t period, void (*callback)(void)) {
	SysTickDisable();					// Disable SysTick during setup
	SysTickPeriodSet(period);			// Set the reload value
    NVIC_ST_CURRENT_R = 0;				// Reset the counter
	SysTickEnable();					// Enable timer

	SysTick_Interrupt_Enable();
    SysTick_Callback = callback;      // Register the callback function
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

void SysTick_Interrupt_Enable(void) {
    SET_BIT(NVIC_ST_CTRL_R, SYSTICK_INTERRUPT);	
}

// Set the SysTick Timer period
void SysTickPeriodSet(uint32_t ui32Period) {
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
uint8_t SysTick_Is_Time_Out(void) {
    return GET_BIT(NVIC_ST_CTRL_R, SYSTICK_COUNT_FLAG);
}

// SysTick Interrupt Handler
void SysTick_Handler(void) {
    if (SysTick_Callback != 0) {
        SysTick_Callback();           // Call the user-defined callback function
    }
}



