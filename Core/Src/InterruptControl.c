/*
 * InterruptControl.c
 *
 *  Created on: Sep 26, 2024
 *      Author: ellis
 */

#include "../Inc/InterruptControl.h"


// FUNCTIONS

void IRQ_EnableInterrupt(uint8_t IRQ){
	HAL_NVIC_EnableIRQ(IRQ);
}
void IRQ_DisableInterrupt(uint8_t IRQ){
	HAL_NVIC_DisableIRQ(IRQ);
}
void IRQ_ClearPendingInterrupt(uint8_t IRQ){
	HAL_NVIC_ClearPendingIRQ(IRQ);
}
void IRQ_SetPendingInterrupt(uint8_t IRQ){
	HAL_NVIC_SetPendingIRQ(IRQ);
}

void ClearPendingEXTIInterrupt(uint8_t pinNum){
	EXTI_HandleTypeDef handleType;
	// get handleType from somewhere?
	HAL_EXTI_ClearPending(&handleType, pinNum);
}
