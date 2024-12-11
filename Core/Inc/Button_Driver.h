/*
 * Button_Driver.h
 *
 *  Created on: Sep 24, 2024
 *      Author: ellis
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include <stdbool.h>

#include "stm32f4xx_hal.h"


// MACROS

#define USE_INTERRUPT_FOR_BUTTON 1

#define EXTI0_IRQ_NUMBER 6
#define BUTTON_PORT	GPIOA
#define BUTTON_PIN	GPIO_PIN_0
#define IS_PRESSED	1
#define NOT_PRESSED	0

// FUNCTION PROTOTYPES

void Button_Init();
void Button_ClockEnable();
void Button_ClockDisable();
bool Button_IsPressed();
void Button_InterruptInit();

#endif /* BUTTON_DRIVER_H_ */
