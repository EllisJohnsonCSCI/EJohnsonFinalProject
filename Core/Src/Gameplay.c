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

// SCREENS

void screen1(void){
	clearScreen();
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);

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
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	clearScreen();

	// Border
	LCD_Draw_Rectangle_Empty(30,10,180,300,LCD_COLOR_BLACK);

	// RNG (generate first block) (maybe unnecessary)
	generateBlock();

	// Timer
	Timer_StartInterrupt();

	// Maybe want to keep scheduler in timer interrupt?
	//vv uncommenting this seems to break touch screen left/right
	/*
	uint8_t eventsToRun = 0;

	while(1){
		eventsToRun = getScheduledEvents();
		if(eventsToRun & ROTATE_BLOCK_EVENT){
			// Rotate
		}
		if(eventsToRun & BLOCK_LEFT_EVENT){
			// Move block left
		}
		if(eventsToRun & BLOCK_RIGHT_EVENT){
			// Move block right
		}
		if(eventsToRun & BLOCK_DOWN_EVENT){
			// Move block down
		}
		if(eventsToRun & APP_DELAY_FLAG_EVENT){
			HAL_Delay(5000); // Maybe shorter
		}
	}
	*/

	// Figure out block stacking & collision

	// Get time
}

void screen3(void){
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	clearScreen();

	// Disable all interrupts

	// Display time
	//String function working will be nice for this
	LCD_DisplayChar(80,40,'3');
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
		LCD_Draw_OBlock(90,250);
		break;
	case 1:
		LCD_Draw_IBlock(105,110,currentOrientation);
		break;
	case 2:
		LCD_Draw_SBlock(170,200,currentOrientation);
		break;
	case 3:
		LCD_Draw_ZBlock(10,200,currentOrientation);
		break;
	case 4:
		LCD_Draw_LBlock(20,10,currentOrientation);
		break;
	case 5:
		LCD_Draw_JBlock(190,10,currentOrientation);
		break;
	case 6:
		LCD_Draw_TBlock(75,35,currentOrientation);
		break;
	default:
		break;
	}
}

void changeOrientation(){
	currentOrientation++;
}
