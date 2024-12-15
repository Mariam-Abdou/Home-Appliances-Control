#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include "tm4c123gh6pm.h"

#define SYSTICK_ENABLE 0
#define SYSTICK_INTERRUPT 1
#define SYSTICK_CLK_SOURCE 2
#define SYSTICK_COUNT_FLAG 16



void SysTickInit(uint32_t period, void (*callback)(void));
void SysTick_Enable(void);
void SysTick_Disable(void);
void SysTick_Interrupt_Enable(void);
void SysTickPeriodSet(uint32_t ui32Period);
uint32_t SysTick_PeriodGet(void);
uint32_t SysTick_ValueGet(void);
uint8_t SysTick_Is_Time_Out(void);
void SysTick_Handler(void);



// Function prototypes for interrupt mode
void SysTick_InitInterrupt(uint32_t reloadValue, void (*callback)(void));

#endif // SYSTICK_H
