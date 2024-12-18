#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "utils.h"

// SysTick Control Register Bit Definitions
#define SYSTICK_ENABLE 0
#define SYSTICK_INTERRUPT 1
#define SYSTICK_CLK_SOURCE 2
#define SYSTICK_COUNT_FLAG 16

void SysTickInit(uint32_t period, void (*callback)(void));
void SysTickEnable(void);
void SysTickDisable(void);
void SysTickInterruptEnable(void);
void SysTickPeriodSet(uint32_t ui32Period);
uint32_t SysTickPeriodGet(void);
void SysTickCurrentSet(uint32_t value);
uint32_t SysTickCurrentGet(void);
uint8_t SysTickIsTimeout(void);
void SysTickHandler(void);

#endif // SYSTICK_H
