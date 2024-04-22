#ifndef FIREEXTINGUISHER_H_
#define FIREEXTINGUISHER_H_

/*
 * This class handles the co2 fire extinguisher and an alarm beeper.
 * If the fire button is pressed or an fire is detected by the gasSensor inside the printer room,
 * a timer starts. In this time the beeper beeps slowly.
 * After FIRE_EXTINGUISHER_TRIGGER_TIMER the co2 valve opens and the beeper beeps faster.
 * After TIME_REDUCE_BEEPER the beeper will be reduced and beeps only one second per minute.
 *
 * While the start timer is running, the procedure can be stopped by pressing the fire button for
 * FIRE_EXTINGUISHER_EXIT_BTN_PRESS_TIME seconds.
 * If it was stopped one time a power cycle is required to activate the fire start timer again.
 */

#include "config.h"
#include "button.h"
#include "printer.h"
#include "gasSensor.h"

typedef struct{
	bool beeperActive;			// 1: beeper sound on
}beeper_t;

typedef struct{
	uint32_t sequenceStartTime; // Time at which an fire is detected and the countdown starts
	uint32_t activatingTime;	// Time at which the valve is opened
	bool valveState;			// 0: Closed, 1: Opened
	bool standby;				// beeper standby after TIME_REDUCE_BEEPER (short beep for one second every minute)
	beeper_t beeper;
}fireExtinguisher_t;
extern fireExtinguisher_t fireExtinguisher;


void fireExtinguisher_init();

/*
 * Here the fire countdown is overwatched and if its running out, the fire extinguisher action starts.
 *
 * If the fire extinguisher countdown has started and the fire button is pressed for more than
 * FIRE_EXTINGUISHER_EXIT_BTN_PRESS_TIME seconds, the alarm will be stopped.
 *
 * The fire extinguisher goes into a standby mode after a specific time
 */
void fireExtinguisher_update();

/*
 * Starts the countdown for the fire extinguisher
 * After FIRE_EXTINGUISHER_TRIGGER_TIMER the CO2 will be released
 */
void fireExtinguisherStartCount();

/*
 * Open the valve for the CO2 and deactivates the pwr supply of the printer
 */
void fireExtinguisherActivate();

/*
 * Stop the alarm and if the valve is already opened, close it again.
 */
void fireExtinguisherStop();

/*
 * Set the beeper control gpio. If the beeper is running longer as TIME_REDUCE_BEEPER
 * change the sound signal to short impulses.
 * This method is called in fireExtinguisher_update();
 */
void beeper_update();

/*
 * Simply sets the variable for the beeper to true. beeper_update() needs to be called
 * otherwise nothing will happen
 */
void beeperStart();

/*
 * Simply sets the variable for the beeper to false. beeper_update() needs to be called
 * otherwise nothing will happen
 */
void beeperStop();

/*
 * Set the valve control gpio for the co2 gas. The used variable can be set to true via a button or
 * an detected fire.
 * This method is called in fireExtinguisher_update()
 */
void valve_update();

#endif
