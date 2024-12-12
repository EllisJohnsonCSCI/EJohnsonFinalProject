/*
 * Scheduler.h
 *
 *  Created on: Sep 10, 2024
 *      Author: ellis
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>


// MACROS

#define ROTATE_BLOCK_EVENT (0x1 << 0)


// FUNCTION PROTOTYPES

uint32_t getScheduledEvents();
void addSchedulerEvent(uint32_t);
void removeSchedulerEvent(uint32_t);


#endif /* SCHEDULER_H_ */
