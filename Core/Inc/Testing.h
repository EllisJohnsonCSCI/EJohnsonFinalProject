/*
 * Testing.h
 *
 *  Created on: Dec 10, 2024
 *      Author: ellis
 */

#ifndef INC_TESTING_H_
#define INC_TESTING_H_

#include "ApplicationCode.h"

#define TESTING_RNG		1
#define TESTING_BUTTON	0
#define TESTING_TIMER	0
#define TESTING_LCD		1

// RNG
void testRNG();

// LCD
void testString();
void testMove();
void testRotate();

#endif /* INC_TESTING_H_ */
