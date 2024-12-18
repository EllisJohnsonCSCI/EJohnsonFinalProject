/*
 * Button_Driver.c
 *
 *  Created on: Sep 24, 2024
 *      Author: ellis
 */

#include "../Inc/Button_Driver.h"

#if USE_INTERRUPT_FOR_BUTTON == 0
void Button_Init(){
	GPIO_InitTypeDef ButtonConfig = {};

	ButtonConfig.Pin = BUTTON_PIN;
	ButtonConfig.Mode = GPIO_MODE_INPUT;
	ButtonConfig.Speed = GPIO_SPEED_FREQ_LOW;

	Button_ClockEnable();
	HAL_GPIO_Init(BUTTON_PORT, &ButtonConfig);
}
#endif

#if USE_INTERRUPT_FOR_BUTTON == 1
void Button_InterruptInit(){
	GPIO_InitTypeDef ButtonConfig = {};

	ButtonConfig.Pin = BUTTON_PIN;
	ButtonConfig.Mode = GPIO_MODE_IT_RISING;
	ButtonConfig.Speed = GPIO_SPEED_FREQ_MEDIUM;
	ButtonConfig.Pull = GPIO_NOPULL;

	Button_ClockEnable();
	HAL_GPIO_Init(BUTTON_PORT, &ButtonConfig);
	HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
#endif

void Button_ClockEnable(){
	__HAL_RCC_GPIOA_CLK_ENABLE();
}

void Button_ClockDisable(){
	__HAL_RCC_GPIOA_CLK_DISABLE();
}

bool Button_IsPressed(){
	if(HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == IS_PRESSED){
		return true;
	}
	else{
		return false;
	}
}
