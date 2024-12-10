/*
 * Timer_Driver.c
 *
 *  Created on: Oct 8, 2024
 *      Author: ellis
 */

#include "../Inc/Timer_Driver.h"

// FUNCTIONS

void Timer_Init(){
	HAL_TIM_Base_Init(&htim6);
	Timer_Reset(&htim6);
	Timer_InterruptEnOrDis(ENABLE);
}

/*
void Timer_ClockControl(uint8_t enOrDis){
	switch(enOrDis){
	case ENABLE:
		TIM_CLK_ENABLE(TIM6EN_BIT_OFFSET);
		break;
	case DISABLE:
		TIM_CLK_DISABLE(TIM6EN_BIT_OFFSET);
	default:
		break;
	}
}
*/

void Timer_Start(){
	HAL_TIM_Base_Start(&htim6);
}

void Timer_Stop(){
	HAL_TIM_Base_Stop(&htim6);
}

void Timer_Reset(){
	__HAL_TIM_SET_COUNTER(&htim6, 0);
}

uint32_t Timer_GetCNT(){
	return __HAL_TIM_GET_COUNTER(&htim6);
}

/*
void Timer_InterruptEnOrDis(uint8_t enOrDis){
	switch(enOrDis){
	case ENABLE:
		IRQ_EnableInterrupt(TIM6_IRQ_NUMBER);
		break;
	case DISABLE:
		IRQ_DisableInterrupt(TIM6_IRQ_NUMBER);
		break;
	default:
		break;
	}
	//Maybe don't need depending on HAL functionality
}
*/

uint32_t Timer_GetARR(){
	return __HAL_TIM_GET_AUTORELOAD(&htim6);
}
