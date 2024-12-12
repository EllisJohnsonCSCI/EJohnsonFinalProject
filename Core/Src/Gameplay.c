/*
 * Gameplay.c
 *
 *  Created on: Dec 11, 2024
 *      Author: ellis
 */

#include "Gameplay.h"

uint8_t timeCount = 0;

uint8_t currentBlock;
uint8_t currentOrientation = 0;
uint8_t currentXpos = STARTING_XPOS;
uint8_t currentYpos = STARTING_YPOS;

// SCREENS

void screen1(void){
	resetScreen();

	// Show all blocks
	LCD_Draw_OBlock(90,250);
	LCD_Draw_IBlock(105,110,0);
	LCD_Draw_SBlock(170,200,0);
	LCD_Draw_ZBlock(10,200,0);
	LCD_Draw_LBlock(20,10,0);
	LCD_Draw_JBlock(190,10,0);
	LCD_Draw_TBlock(75,35,0);

	// "Tetris"
	LCD_DisplayChar(80,40,'T');
	LCD_DisplayChar(95,40,'E');
	LCD_DisplayChar(110,40,'T');
	LCD_DisplayChar(125,40,'R');
	LCD_DisplayChar(135,40,'I');
	LCD_DisplayChar(145,40,'S');

	// Start button
	LCD_DisplayChar(95,200,'S');
	LCD_DisplayChar(105,200,'t');
	LCD_DisplayChar(115,200,'a');
	LCD_DisplayChar(125,200,'r');
	LCD_DisplayChar(132,200,'t');
	LCD_Draw_Rectangle_Empty(70,160,100,100,LCD_COLOR_BLACK);
}

void screen2(void){
	//10 tall x 6 wide
	//30*10 = 300
	//30*6 = 180
	resetScreen();

	// Border
	//LCD_Draw_Rectangle_Empty(30,10,180,300,LCD_COLOR_BLACK);

	// RNG (generate first block)
	generateBlock();

	// Timer
	Timer_StartInterrupt();

	// Lose conditions = tapping screen 5 times

	// Figure out block stacking & collision (probably too ambitious)
}

void screen3(void){
	resetScreen();

	// "Time:"
	LCD_DisplayChar(80,40,'T');
	LCD_DisplayChar(90,40,'i');
	LCD_DisplayChar(100,40,'m');
	LCD_DisplayChar(115,40,'e');
	LCD_DisplayChar(125,40,':');

	// Display time
	//Divide into individual integers
	uint8_t num = (timeCount * 3);
	uint8_t count = 0;
	if(num/100 >= 1){
		while(num > 99){
			num -= 100;
			count++;
		}
	}
	LCD_DisplayChar(80, 80, count + '0');
	count = 0;
	if(num/10 >= 1){
		while(num > 9){
			num -= 10;
			count++;
		}
	}
	LCD_DisplayChar(100, 80, count + '0');
	LCD_DisplayChar(120, 80, num + '0');
}

void resetScreen(){
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	clearScreen();
}

// BLOCK LOGIC

void generateBlock(){
	RNG_Init();

	currentBlock = RNG_Generate() % 7;
	drawBlock();

	RNG_DeInit();
}

void drawBlock(){
	switch(currentBlock){
	case 0:
		LCD_Draw_OBlock(currentXpos,currentYpos);
		break;
	case 1:
		LCD_Draw_IBlock(currentXpos,currentYpos,currentOrientation);
		break;
	case 2:
		LCD_Draw_SBlock(currentXpos,currentYpos,currentOrientation);
		break;
	case 3:
		LCD_Draw_ZBlock(currentXpos,currentYpos,currentOrientation);
		break;
	case 4:
		LCD_Draw_LBlock(currentXpos,currentYpos,currentOrientation);
		break;
	case 5:
		LCD_Draw_JBlock(currentXpos,currentYpos,currentOrientation);
		break;
	case 6:
		LCD_Draw_TBlock(currentXpos,currentYpos,currentOrientation);
		break;
	default:
		break;
	}
}

void rotateBlock(){
	currentOrientation++;
}
void resetPosition(){
	currentXpos = STARTING_XPOS;
	currentYpos = STARTING_YPOS;
}
void moveBlockDown(){
	currentYpos += BLOCK_LENGTH;
}
void moveBlockRight(){
	currentXpos += BLOCK_LENGTH;
}
void moveBlockLeft(){
	currentXpos -= BLOCK_LENGTH;
}
