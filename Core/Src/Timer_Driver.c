/*
 * Timer_Driver.c
 *
 *  Created on: Oct 8, 2024
 *      Author: ellis
 */

#include "../Inc/Timer_Driver.h"

TIM_HandleTypeDef htim7;


// FUNCTIONS

void Timer_Init(){
	htim7.Instance = TIM7;
	htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	htim7.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim7.Init.Period = PERIOD;
	htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim7.Init.Prescaler = PRESCALER;

	Timer_ClockControl(ENABLE);
	Timer_Error_Handler(HAL_TIM_Base_Init(&htim7));
	Timer_Reset();
}

void Timer_ClockControl(uint8_t enOrDis){
	if(enOrDis == ENABLE){
		__HAL_RCC_TIM7_CLK_ENABLE();
	}
	else{
		__HAL_RCC_TIM7_CLK_DISABLE();
	}
}

#if USE_INTERRUPT_FOR_TIMER == 0
void Timer_Start(){
	HAL_TIM_Base_Start(&htim7);
}

void Timer_Stop(){
	HAL_TIM_Base_Stop(&htim7);
}
#endif

#if USE_INTERRUPT_FOR_TIMER == 1
void Timer_StartInterrupt(){
	Timer_Error_Handler(HAL_TIM_Base_Start_IT(&htim7));
}

void Timer_StopInterrupt(){
	Timer_Error_Handler(HAL_TIM_Base_Stop_IT(&htim7));
}
#endif

void Timer_Reset(){
	__HAL_TIM_SET_COUNTER(&htim7, 0);
}

uint32_t Timer_GetCNT(){
	return __HAL_TIM_GET_COUNTER(&htim7);
}

uint32_t Timer_GetARR(){
	return __HAL_TIM_GET_AUTORELOAD(&htim7);
}

void Timer_Error_Handler(HAL_StatusTypeDef input){
	if(input != HAL_OK){
		for(;;);
	}
}
