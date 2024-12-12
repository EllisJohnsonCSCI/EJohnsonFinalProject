/*
 * Gameplay.h
 *
 *  Created on: Dec 11, 2024
 *      Author: ellis
 */

#ifndef INC_GAMEPLAY_H_
#define INC_GAMEPLAY_H_

#include "LCD_Driver.h"

#define STARTING_XPOS	110
#define STARTING_YPOS	30

void screen1(void);
void screen2(void);
void screen3(void);

void resetScreen();

void generateBlock();
void drawBlock();
void changeOrientation();
void resetPosition();
void moveBlockDown();
void moveBlockRight();
void moveBlockLeft();

#endif /* INC_GAMEPLAY_H_ */
