#ifndef FIREEXTINGUISHER_H_
#define FIREEXTINGUISHER_H_

#include "config.h"
#include "button.h"

typedef struct{
	bool beeperActive;
}beeper_t;

typedef struct{
	uint32_t sequenceStartTime; // Time at which an fire is detected and the countdown starts
	uint32_t activatingTime;	// Time at which the valve is opened
	bool valveState;			// 0: Closed, 1: Opened
	bool standby;
	beeper_t beeper;
}fireExtinguisher_t;
extern fireExtinguisher_t fireExtinguisher;


void fireExtinguisher_init();
void fireExtinguisher_update();

void fireExtinguisherStartCount();
void fireExtinguisherActivate();
void fireExtinguisherStop();

void beeper_update();
void beeperStart();
void beeperStop();

void valve_update();

#endif
