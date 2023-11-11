#include "fireExtinguisher.h"

fireExtinguisher_t fireExtinguisher;

void fireExtinguisher_init(){
	fireExtinguisher.sequenceStartTime = 0;
	fireExtinguisher.activatingTime = 0;
	fireExtinguisher.valveState = CLOSED;
	fireExtinguisher.standby = false;

	fireExtinguisher.beeper.beeperActive = false;
}

void fireExtinguisher_update(){
	beeper_update(); // Update Beeper
	valve_update();	 // Update valve

	// Stop if there is no fire detected
	if(fireExtinguisher.sequenceStartTime == 0)
		return;

	if(getButtonState(BUTTON_FIRE_EXTINGUISHER) && getButtonPressedTime() > FIRE_EXTINGUISHER_EXIT_BTN_PRESS_TIME)
		fireExtinguisherStop();

	// Start extinguishing action
	if(HAL_GetTick() > fireExtinguisher.activatingTime + FIRE_EXTINGUISHER_TRIGGER_TIMER)
		fireExtinguisherActivate();

	// Reduce the beeper and the LED fade after a defined time
	if(HAL_GetTick() > fireExtinguisher.activatingTime + TIME_REDUCE_BEEPER)
		fireExtinguisher.standby = true;
		// Note: Beeper change is handled in beeper_update() in printerHousingCtrl.c
		// Note: LEDs going into off state handled in printerHousingCtrl.c
}

void fireExtinguisherStartCount(){
	fireExtinguisher.sequenceStartTime = HAL_GetTick(); // Countdown starts

	beeperStart(); // Activate Beeper

	// Note: Now leds are fading red handled in printerHousingCtrl.c)
}

void fireExtinguisherActivate(){
	// Set time valve opened
	fireExtinguisher.activatingTime = HAL_GetTick();

	// Shutdown printer
	printerShutdown();

	// Open valve
	fireExtinguisher.valveState = OPENED;
}

void fireExtinguisherStop(){
	fireExtinguisher.sequenceStartTime = fireExtinguisher.activatingTime = 0; // Reset timer
	beeperStop(); 							// Stop beeper
	fireExtinguisher.valveState = CLOSED;	// Close valve if opened
}

void beeper_update(){
	// If beeper should not be active, mute and return the method
	if (fireExtinguisher.beeper.beeperActive){
		HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, LOW);
		return;
	}

	// First beep fast, after TIME_REDUCE_BEEPER beep every minute for one second
	if(fireExtinguisher.activatingTime < HAL_GetTick() + TIME_REDUCE_BEEPER)
		HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, HAL_GetTick() % 400 < 200);
	else
		HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, HAL_GetTick() % 60000 < 1000);
}

void beeperStart(){
	fireExtinguisher.beeper.beeperActive = true;
}

void beeperStop(){
	fireExtinguisher.beeper.beeperActive = false;
}

void valve_update(){
	HAL_GPIO_WritePin(valve_open_GPIO_Port, valve_open_Pin, fireExtinguisher.valveState);
}


