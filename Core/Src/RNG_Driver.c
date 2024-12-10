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
	HAL_RNG_Init(&hrng);
}

uint32_t RNG_Generate(){
	uint32_t num;
	HAL_RNG_GenerateRandomNumber(&hrng, &num);
	return num;
}

void RNG_DeInit(){
	HAL_RNG_DeInit(&hrng);
	RNG_ClockControl(DISABLE);
}
