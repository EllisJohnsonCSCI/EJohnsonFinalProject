/*
 * RNG_Driver.h
 *
 *  Created on: Dec 10, 2024
 *      Author: ellis
 */

#ifndef INC_RNG_DRIVER_H_
#define INC_RNG_DRIVER_H_


#include "stm32f4xx_hal.h"


void RNG_ClockControl(uint8_t);
void RNG_Init();
uint32_t RNG_Generate();
void RNG_DeInit();
void RNG_Error_Handler(HAL_StatusTypeDef);

#endif /* INC_RNG_DRIVER_H_ */
