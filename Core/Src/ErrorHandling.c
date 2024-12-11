/*
 * ErrorHandling.c
 *
 *  Created on: Nov 5, 2024
 *      Author: ellis
 */


#include "../Inc/ErrorHandling.h"


// FUNCTIONS

void APPLICATION_ASSERT(bool input){
	if(!input){
		for(;;);
	}
}
