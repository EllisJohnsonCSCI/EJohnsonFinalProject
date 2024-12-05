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

#define APP_DELAY_FLAG_EVENT (0x1 << 0)
#define ROTATE_BLOCK_EVENT (0x1 << 1)


// FUNCTION PROTOTYPES

uint32_t getScheduledEvents();
void addSchedulerEvent(uint32_t);
void removeSchedulerEvent(uint32_t);


#endif /* SCHEDULER_H_ */
