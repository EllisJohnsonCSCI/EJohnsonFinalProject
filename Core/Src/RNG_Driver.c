/*
 * RNG_Driver.c
 *
 *  Created on: Dec 10, 2024
 *      Author: ellis
 */

#include "RNG_Driver.h"

RNG_HandleTypeDef hrng;

// FUNCTIONS

void RNG_ClockControl(uint8_t enOrDis){
	if(enOrDis == ENABLE){
		__HAL_RCC_RNG_CLK_ENABLE();
	}
	else{
		__HAL_RCC_RNG_CLK_DISABLE();
	}
}

void RNG_Init(){
	RNG_ClockControl(ENABLE);
	RNG_Error_Handler(HAL_RNG_Init(&hrng));
}

uint32_t RNG_Generate(){
	uint32_t num;
	RNG_Error_Handler(HAL_RNG_GenerateRandomNumber(&hrng, &num));
	return num;
}

void RNG_DeInit(){
	RNG_Error_Handler(HAL_RNG_DeInit(&hrng));
	RNG_ClockControl(DISABLE);
}

void RNG_Error_Handler(HAL_StatusTypeDef input){
	if(input != HAL_OK){
		for(;;);
	}
}
