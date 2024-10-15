#include "fireExtinguisher.h"

fireExtinguisher_t fireExtinguisher;
fireButtonState_t buttonStopped = BUTTON_STOPPED_NONE;

void fireExtinguisher_init(){
	fireExtinguisher.sequenceStartTime = 0;
	fireExtinguisher.activatingTime = 0;
	fireExtinguisher.valveState = CLOSED;
	fireExtinguisher.standby = false;

	fireExtinguisher.beeper.beeperActive = false;
	HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, LOW); // Init beeper off
}

void fireExtinguisher_update(){
	beeper_update(); // Update Beeper

	// Reset saved button state by pressing the fire button again after an detected fire was stopped by pressing the fire button
	if (getButtonState(BUTTON_FIRE_EXTINGUISHER) && buttonStopped == BUTTON_STOPPED_SEQUENCE){
		buttonStopped = BUTTON_STOPPED_NONE;
		return;
	}

	// If a detected fire alarm was stopped by pressing the fire button, it must not be
	// possible to start the alarm again
	if(buttonStopped == BUTTON_STOPPED_SEQUENCE)
		return;

	// Activate fire extinguisher sequence if fire is detected
	if ((getButtonState(BUTTON_FIRE_EXTINGUISHER) || gasSensor.fireDetected) && fireExtinguisher.sequenceStartTime == 0){
		fireExtinguisherStartCount();
		return;
	}

	// Stop if there is no fire detected
	if(fireExtinguisher.sequenceStartTime == 0)
		return;

	// Press the fire butto one time to deactivate the beeper
	// Press a second time, to deactivate the extinguisher sequence
	if (getButtonState(BUTTON_FIRE_EXTINGUISHER)) {
		if (buttonStopped == BUTTON_STOPPED_NONE) {
			beeperStop();
			buttonStopped = BUTTON_STOPPED_MUTE;
		} else {
			fireExtinguisherStop();
			buttonStopped = BUTTON_STOPPED_SEQUENCE;
			return;
		}
	}

	// Start extinguishing action after defined time
	if(HAL_GetTick() > (fireExtinguisher.sequenceStartTime + FIRE_EXTINGUISHER_TRIGGER_TIMER))
		fireExtinguisherActivate();

	// Reduce the beeper and the LED fade after a defined time, valve stays opened
	if(HAL_GetTick() > fireExtinguisher.activatingTime + TIME_REDUCE_BEEPER && fireExtinguisher.activatingTime != 0)
		fireExtinguisher.standby = true;
		// Note: Beeper change is handled in beeper_update()
		// Note: LEDs going into off state handled in printerHousingCtrl.c
}

void fireExtinguisherStartCount(){
	if(buttonStopped != BUTTON_STOPPED_NONE) // If the fire countdown has stopped by pressing the button, dont start again
		return;
	if(fireExtinguisher.sequenceStartTime != 0) // Alarm already started
		return;

	fireExtinguisher.sequenceStartTime = HAL_GetTick(); // Set time countdown starts
	beeperStart(); // Activate Beeper

	// Now LEDs are fading red handled in led.c
}

void fireExtinguisherActivate(){
	beeperStart();
	if(fireExtinguisher.activatingTime != 0) // Stop if extinguisher is already activated
		return;

	fireExtinguisher.activatingTime = HAL_GetTick(); // Set time valve opened
	printerShutdown(); 	// Shutdown printer
	valveOpen(); // Open valve
}

void fireExtinguisherStop(){
	fireExtinguisher.sequenceStartTime = fireExtinguisher.activatingTime = 0; // Reset timer
	beeperStop(); 	// Stop beeper
	valveClose();	// Close valve if opened
}

void beeper_update(){
	// If beeper should not be active, mute and return the method
	if (!fireExtinguisher.beeper.beeperActive){
		HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, LOW);
		return;
	}

	// First beep fast, after TIME_REDUCE_BEEPER beep every minute for one second
	if (fireExtinguisher.sequenceStartTime != 0 && !fireExtinguisher.valveState)
		HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, HAL_GetTick() % 2000 < 1000);
	else if (!fireExtinguisher.standby)
		HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, HAL_GetTick() % 600 < 300);
	else
		// After TIME_REDUCE_BEEPER beep only one second in one minute
		HAL_GPIO_WritePin(beeper_GPIO_Port, beeper_Pin, HAL_GetTick() % 60000 < 1000);
}

void beeperStart(){
	fireExtinguisher.beeper.beeperActive = true;
}

void beeperStop(){
	fireExtinguisher.beeper.beeperActive = false;
}

void valveOpen(){
	HAL_GPIO_WritePin(valve_open_GPIO_Port, valve_open_Pin, true);
	fireExtinguisher.valveState = OPENED;
}

void valveClose(){
	HAL_GPIO_WritePin(valve_open_GPIO_Port, valve_open_Pin, false);
	fireExtinguisher.valveState = CLOSED;
}
