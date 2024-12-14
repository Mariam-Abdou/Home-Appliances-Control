#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"

#define SYSTICK_ENABLE 0
#define SYSTICK_INTERRUPT 1
#define SYSTICK_CLK_SOURCE 2
#define SYSTICK_COUNT_FLAG 16



// Function prototypes
void SysTick_Init(uint32_t reloadValue);
void SysTick_Enable(void);
void SysTick_Disable(void);
void SysTick_PeriodSet(uint32_t ui32Period);
uint32_t SysTick_PeriodGet(void);
uint32_t SysTick_ValueGet(void);
bool SysTick_Is_Time_Out(void);

// Function prototypes for interrupt mode
void SysTick_InitInterrupt(uint32_t reloadValue, void (*callback)(void));

#endif // SYSTICK_H
