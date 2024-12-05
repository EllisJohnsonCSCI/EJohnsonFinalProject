/*
 * Timer_Driver.h
 *
 *  Created on: Oct 8, 2024
 *      Author: ellis
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include <stdbool.h>

#include "InterruptControl.h"
#include "stm32f4xx_hal.h"


// STRUCTS

typedef struct{
	bool UDIS;		// Update Disable
	bool OPM;		// One Pulse Mode Enable
	bool DIR;		// Direction
	uint8_t CMS;	// Center-Aligned Mode Selection
	bool ARPE;		// Auto Reload Buffer/Preload Enable
	uint8_t CKD;	// Clock Division Select
	uint8_t MMS;	// Master Mode Selection
	bool UIE;		// Interrupt Update Enable
	uint16_t PSC;	// Prescaler Value
	uint32_t ARR;	// Auto Reload Value
}GPTimer_Config_t;


// MACROS

//Center-Aligned Modes
#define GPTIMR_CMS_EA	0
#define GPTIMR_CMS_CAD	1
#define GPTIMR_CMS_CAU	2
#define GPTIMR_CMS_CAUD	3

//CKD Modes
#define GPTIMR_CKD_1	0
#define GPTIMR_CKD_2	1
#define GPTIMR_CKD_4	2

//MMS Modes
#define GPTIMR_MMS_RESET			0
#define GPTIMR_MMS_ENABLE			1
#define GPTIMR_MMS_UPDATE			2
#define GPTIMR_MMS_COMPARE_PULSE	3
#define GPTIMR_MMS_COMPARE_OC1REF	4
#define GPTIMR_MMS_COMPARE_OC2REF	5
#define GPTIMR_MMS_COMPARE_OC3REF	6
#define GPTIMR_MMS_COMPAREOC4REF	7

//Constants
#define DOUBLE 2


// FUNCTION PROTOTYPES

void initializeTimer(GPTIMR_RegDef_t*, GPTimer_Config_t);
void timerClockControl(GPTIMR_RegDef_t*, uint8_t);
void startTimer(GPTIMR_RegDef_t*);
void stopTimer(GPTIMR_RegDef_t*);
void resetTimer(GPTIMR_RegDef_t*);
uint32_t getTimerCNT(GPTIMR_RegDef_t*);
void timerInterruptEnOrDis(GPTIMR_RegDef_t*, uint8_t);
uint32_t getTimerARR(GPTIMR_RegDef_t*);


#endif /* TIMER_DRIVER_H_ */
