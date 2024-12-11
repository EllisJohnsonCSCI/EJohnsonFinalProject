/*
 * Timer_Driver.h
 *
 *  Created on: Oct 8, 2024
 *      Author: ellis
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_


#include "stm32f4xx_hal.h"


// MACROS

#define USE_INTERRUPT_FOR_TIMER	1

#define PRESCALER	4999
#define PERIOD		0xFFFF

// FUNCTION PROTOTYPES

void Timer_Init();
void Timer_ClockControl(uint8_t);
void Timer_Start();
void Timer_Stop();
void Timer_StartInterrupt();
void Timer_StopInterrupt();
void Timer_Reset();
uint32_t Timer_GetCNT();
uint32_t Timer_GetARR();
void Timer_Error_Handler(HAL_StatusTypeDef);

#endif /* TIMER_DRIVER_H_ */
