/*
 * Timer_Driver.c
 *
 *  Created on: Oct 8, 2024
 *      Author: ellis
 */

#include "../Inc/Timer_Driver.h"

extern TIM_HandleTypeDef htim6;


// FUNCTIONS

void Timer_Init(){
	HAL_TIM_Base_Init(&htim6);
	Timer_Reset(&htim6);
}

#if USE_INTERRUPT_FOR_TIMER == 0
void Timer_Start(){
	HAL_TIM_Base_Start(&htim6);
}

void Timer_Stop(){
	HAL_TIM_Base_Stop(&htim6);
}
#endif

#if USE_INTERRUPT_FOR_TIMER == 1
void Timer_StartInterrupt(){
	HAL_TIM_Base_Start_IT(&htim6);
}

void Timer_StopInterrupt(){
	HAL_TIM_Base_Stop_IT(&htim6);
}
#endif

void Timer_Reset(){
	__HAL_TIM_SET_COUNTER(&htim6, 0);
}

uint32_t Timer_GetCNT(){
	return __HAL_TIM_GET_COUNTER(&htim6);
}

uint32_t Timer_GetARR(){
	return __HAL_TIM_GET_AUTORELOAD(&htim6);
}
