/*
 * Testing.c
 *
 *  Created on: Dec 10, 2024
 *      Author: ellis
 */

#include "Testing.h"

void testRNG(){
	RNG_Init();
	uint32_t generatedNum = RNG_Generate();
	LCD_DisplayChar(150, 40, generatedNum);	//might not work without casting to uint8_t

	//Display block
	switch(generatedNum){
	case 0:
		LCD_Draw_OBlock(90,250);
		LCD_Draw_IBlock(105,110);
		LCD_Draw_SBlock(170,200);
		LCD_Draw_ZBlock(10,200);
		LCD_Draw_LBlock(20,10);
		LCD_Draw_JBlock(190,10);
		LCD_Draw_TBlock(75,35);
		break;
	default:
		break;
	}
	RNG_DeInit();
}
