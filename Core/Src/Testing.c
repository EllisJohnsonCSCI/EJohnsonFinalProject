/*
 * Testing.c
 *
 *  Created on: Dec 10, 2024
 *      Author: ellis
 */

#include "Testing.h"

/* RNG */

void testRNG(){
	RNG_Init();
	uint32_t generatedNum = RNG_Generate();

	// Display block
	switch(generatedNum % 7){
	case 0:
		LCD_Draw_OBlock(90,250);
		break;
	case 1:
		LCD_Draw_IBlock(105,110,0);
		break;
	case 2:
		LCD_Draw_SBlock(170,200,0);
		break;
	case 3:
		LCD_Draw_ZBlock(10,200,0);
		break;
	case 4:
		LCD_Draw_LBlock(20,10,0);
		break;
	case 5:
		LCD_Draw_JBlock(190,10,0);
		break;
	case 6:
		LCD_Draw_TBlock(75,35,0);
		break;
	default:
		break;
	}

	RNG_DeInit();
}

/* LCD */

void testString(){
	LCD_DisplayChar(80,40,'T');
	uint8_t string[] = "TETRIS";
	LCD_DisplayString(80, 40, string);
}

void testMove(){
	uint8_t xpos = 20;
	uint8_t ypos = 10;
	uint8_t testLayer = 0;

	//Draw block
	LCD_Draw_LBlock(xpos,ypos,0);
	while(1){
		HAL_Delay(5000);
		//Want to use layers? Clear layer with current block only
		LCD_Clear(testLayer, LCD_COLOR_WHITE);
		//Draw block 30px down
		LCD_Draw_LBlock(xpos, ypos+BLOCK_LENGTH, 0);
		ypos += BLOCK_LENGTH;
	}
	//Layer 0 = border, set blocks (things with collision)
	//Layer 1 = current block
}

void testRotate(){
	uint8_t xpos = 20;
	uint8_t ypos = 10;
	uint8_t orientation = 0;
	uint8_t testLayer = 0;

	//Draw block
	LCD_Draw_LBlock(xpos, ypos, orientation);
	while(1){
		HAL_Delay(5000);
		//Want to use layers? Clear layer with current block only
		LCD_Clear(testLayer, LCD_COLOR_WHITE);
		orientation++;
		//Rotate block
		LCD_Draw_LBlock(xpos, ypos+BLOCK_LENGTH, orientation);
	}
}
