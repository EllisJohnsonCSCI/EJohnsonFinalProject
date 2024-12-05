/*
 * Timer_Driver.c
 *
 *  Created on: Oct 8, 2024
 *      Author: ellis
 */

#include "../Inc/Timer_Driver.h"

// FUNCTIONS

void initializeTimer(GPTIMR_RegDef_t *TIMx, GPTimer_Config_t timerConfig){
	uint32_t temp = 0;

	//UDIS: bit 1 in CR1
	temp = (timerConfig.UDIS << 1);
	TIMx->TIM_CR[0] &= ~(0x1 << 1); // clear
	TIMx->TIM_CR[0] |= temp; // set

	//OPM: bit 3 in CR1
	temp = (timerConfig.OPM << 3);
	TIMx->TIM_CR[0] &= ~(0x1 << 3); // clear
	TIMx->TIM_CR[0] |= temp; // set

	//DIR: bit 4 in CR1
	temp = (timerConfig.DIR << 4);
	TIMx->TIM_CR[0] &= ~(0x1 << 4); // clear
	TIMx->TIM_CR[0] |= temp; // set

	//CMS: bits 6:5 in CR1
	temp = (timerConfig.CMS << 5);
	TIMx->TIM_CR[0] &= ~(0x3 << 5); // clear
	TIMx->TIM_CR[0] |= temp; // set

	//ARPE: bit 7 in CR1
	temp = (timerConfig.ARPE << 7);
	TIMx->TIM_CR[0] &= ~(0x1 << 7); // clear
	TIMx->TIM_CR[0] |= temp; // set

	//CKD: bits 9:8 in CR1
	temp = (timerConfig.CKD << 8);
	TIMx->TIM_CR[0] &= ~(0x3 << 8); // clear
	TIMx->TIM_CR[0] |= temp; // set

	//MMS: bits 6:4 in CR2
	temp = (timerConfig.MMS << 4);
	TIMx->TIM_CR[1] &= ~(0x1 << 4); // clear
	TIMx->TIM_CR[1] |= temp; // set

	//UIE: bit 0 in DIER
	temp = (timerConfig.UIE << 0);
	TIMx->TIM_DIER &= ~(0x1 << 0); // clear
	TIMx->TIM_DIER |= temp; // set

	//PSC
	temp = (timerConfig.PSC << 0);
	TIMx->TIM_PSC &= ~(0xFFFF << 0); // clear
	TIMx->TIM_PSC |= temp; // set

	//ARR
	temp = (timerConfig.ARR << 0);
	TIMx->TIM_ARR &= ~(0xFFFFFFFF << 0); // clear
	TIMx->TIM_ARR |= temp; // set

	resetTimer(TIMx);

	//if(TIMx == TIM2){
	timerInterruptEnOrDis(TIMx, ENABLE);
	//}
}

void timerClockControl(GPTIMR_RegDef_t *TIMx, uint8_t enOrDis){
	switch(enOrDis){
	case ENABLE:
		if(TIMx == TIM2){
			TIM_CLK_ENABLE(TIM2EN_BIT_OFFSET);
		}
		else if(TIMx == TIM5){
			TIM_CLK_ENABLE(TIM5EN_BIT_OFFSET);
		}
		break;
	case DISABLE:
			if(TIMx == TIM2){
				TIM_CLK_DISABLE(TIM2EN_BIT_OFFSET);
			}
			else if(TIMx == TIM5){
				TIM_CLK_DISABLE(TIM5EN_BIT_OFFSET);
			}
			break;
	default:
		break;
	}
}

void startTimer(GPTIMR_RegDef_t *TIMx){
	TIMx->TIM_CR[0] |= 0x1;
}

void stopTimer(GPTIMR_RegDef_t *TIMx){
	TIMx->TIM_CR[0] &= ~(0x1);
}

void resetTimer(GPTIMR_RegDef_t *TIMx){
	//Set the CNT value to zero for the timer
	TIMx->TIM_CNT &= ~(0xFFFFFFFF);
}

uint32_t getTimerCNT(GPTIMR_RegDef_t *TIMx){
	return TIMx->TIM_CNT;
}

void timerInterruptEnOrDis(GPTIMR_RegDef_t *TIMx, uint8_t enOrDis){
	switch(enOrDis){
	case ENABLE:
		if(TIMx == TIM2){
			IRQ_EnableInterrupt(TIM2_IRQ_NUMBER);
		}
		else if(TIMx == TIM5){
			IRQ_EnableInterrupt(TIM5_IRQ_NUMBER);
		}
		break;
	case DISABLE:
			if(TIMx == TIM2){
				IRQ_DisableInterrupt(TIM2_IRQ_NUMBER);
			}
			else if(TIMx == TIM5){
				IRQ_DisableInterrupt(TIM5_IRQ_NUMBER);
			}
			break;
	default:
		break;
	}
}

uint32_t getTimerARR(GPTIMR_RegDef_t *TIMx){
	return TIMx->TIM_ARR;
}
