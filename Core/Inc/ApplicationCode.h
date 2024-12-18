/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "stm32f4xx_hal.h"
#include "Gameplay.h"
#include "Button_Driver.h"
#include "Timer_Driver.h"
#include "RNG_Driver.h"
#include "Scheduler.h"

#include <stdio.h>

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

void ApplicationInit(void);
void LCD_Visual_Demo(void);

#if (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)

#endif /* INC_APPLICATIONCODE_H_ */

#if USE_INTERRUPT_FOR_BUTTON == 0
void buttonInit();
void executeButtonPollingRoutine();
#endif
#if USE_INTERRUPT_FOR_BUTTON == 1
void buttonInitInterrupt();
#endif

void timerInit();
