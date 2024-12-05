/*
 * Scheduler.c
 *
 *  Created on: Sep 10, 2024
 *      Author: ellis
 */

#include "../Inc/Scheduler.h"

// Contains events that need to be run
static uint32_t scheduledEvents;

uint32_t getScheduledEvents(){
	return scheduledEvents;
}

void addSchedulerEvent(uint32_t eventToSchedule){
	scheduledEvents |= eventToSchedule; // Set
}

void removeSchedulerEvent(uint32_t eventToRemove){
	scheduledEvents &= ~eventToRemove; // Clear
}
