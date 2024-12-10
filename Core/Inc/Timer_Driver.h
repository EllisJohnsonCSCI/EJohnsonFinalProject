/*
 * Timer_Driver.h
 *
 *  Created on: Oct 8, 2024
 *      Author: ellis
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include <stdbool.h>

#include "InterruptControl.h"
#include "stm32f4xx_hal.h"


// MACROS / VARS
#define DOUBLE 2
TIM_HandleTypeDef htim6;

// FUNCTION PROTOTYPES

void Timer_Init();
void Timer_ClockControl(uint8_t);
void Timer_Start();
void Timer_Stop();
void Timer_Reset();
uint32_t Timer_GetCNT();
void Timer_InterruptEnOrDis(uint8_t);
uint32_t Timer_GetARR();

#endif /* TIMER_DRIVER_H_ */
