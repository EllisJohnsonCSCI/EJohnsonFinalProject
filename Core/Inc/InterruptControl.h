/*
 * InterruptControl.h
 *
 *  Created on: Sep 26, 2024
 *      Author: ellis
 */

#ifndef INTERRUPTCONTROL_H_
#define INTERRUPTCONTROL_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"


// MACROS

#define EXTI0_IRQ_NUMBER 6


// FUNCTION PROTOTYPES

void IRQ_EnableInterrupt(uint8_t);
void IRQ_DisableInterrupt(uint8_t);
void IRQ_ClearPendingInterrupt(uint8_t);
void IRQ_SetPendingInterrupt(uint8_t);

void ClearPendingEXTIInterrupt(uint8_t);


#endif /* INTERRUPTCONTROL_H_ */
