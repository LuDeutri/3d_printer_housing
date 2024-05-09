#include "led.h"

led_t leds;
clock_t startTimeTimeExpired;

bool startAnimation;
uint32_t runningLightTime1;
int32_t runningLightCounter1;
uint32_t runningLightTime2;
int32_t runningLightCounter2;

clock_t startTimeLightElectronicsRoom;

void led_init(){
	leds.ledDataIn = 0;
	leds.state = LED_STATE_WHITE;
	leds.ledPiDataUsed = false;
	leds.usedLedPiDataInput = LED_STATE_OFF;

	startAnimation = ENABLE_START_ANIMATION;

	startTimeTimeExpired = 0;
	runningLightTime1 = 0;
	runningLightCounter1 = 0;

	runningLightTime2 = 0;
	runningLightCounter2 = 0;

	startTimeLightElectronicsRoom = 0;

	ws281x_init();
	setBrightness(LED_BRIGHTNESS);
}

void led_update() {
	// Start animation
	if(startAnimation){
		startAnimationLED();
		return;
	}

	// Set the light in the electronics room off after LIGHT_TIME_ELECTRONICS_ROOM milliseconds
	if(HAL_GetTick() > startTimeLightElectronicsRoom + LIGHT_TIME_ELECTRONICS_ROOM && startTimeLightElectronicsRoom != 0){
		startTimeLightElectronicsRoom = 0;
		setAllLEDs(off);
	}

	// Fire detected led mode
	if(fireExtinguisher.activatingTime != 0)
		nextStateLED(LED_STATE_RED_FADE);
	// Update LEDs depending on raspi pi data input
	else if (leds.ledDataIn != leds.usedLedPiDataInput){
		leds.usedLedPiDataInput = leds.ledDataIn; 	// Store the data in usedDataInput to be sure its only one time updated with the same data
		nextStateLED(leds.ledDataIn);
	// Button ctrl, next state if button pressed
	} else if (getButtonState(BUTTON_LED)){
		if(startTimeLightElectronicsRoom == 0){ // If the light in the electronics room is not active, activate it
			if(leds.state == LED_STATE_OFF){
				nextState();
				return;
			}
			setSpecificLEDs(white, 0, NUM_LED_STRIP_BOTTOM_RIGHT);
			setSpecificLEDs(white, INDEX_LED_STRIP_BOTTOM_RIGHT, NUM_LED);
			startTimeLightElectronicsRoom = HAL_GetTick();
		} else // If the light is already active, go into the next led state for the printer room leds
			nextState();
	}

	switch(leds.state){
	case LED_STATE_OFF:
		setAllLEDs(off);
		startTimeLightElectronicsRoom = 0;
	break;
	case LED_STATE_WHITE:
		setSpecificLEDs(white, INDEX_LED_STRIP_LEFT, INDEX_LED_STRIP_BOTTOM_RIGHT);
	break;
	case LED_STATE_GREEN:
		setSpecificLEDs(green, INDEX_LED_STRIP_LEFT, INDEX_LED_STRIP_BOTTOM_RIGHT);
	break;
	case LED_STATE_BLUE:
		setSpecificLEDs(blue, INDEX_LED_STRIP_LEFT, INDEX_LED_STRIP_BOTTOM_RIGHT);
	break;
	case LED_STATE_RED:
		setSpecificLEDs(red, INDEX_LED_STRIP_LEFT, INDEX_LED_STRIP_BOTTOM_RIGHT);
	break;
	case LED_STATE_GREEN_FADE:
		fadeOneColor(green, INDEX_LED_STRIP_LEFT, INDEX_LED_STRIP_BOTTOM_RIGHT);
	break;
	case LED_STATE_RED_FADE:
		fadeOneColor(red, INDEX_LED_STRIP_LEFT, INDEX_LED_STRIP_BOTTOM_RIGHT);
	break;
	case LED_STATE_COLOR_FADE:
		fadeColorWheel();
	break;
	default:
		// You should never be here
	break;
	}
	ws281x_send(); // Update led string
}

void startAnimationLED(){
	// Set start animation to finished if one running light cylce reach the end
	if(runningLight(red, 0, FORWARD, true, &runningLightTime1, &runningLightCounter1)
			|| runningLight(blue, NUM_LED, BACKWARD, false, &runningLightTime2, &runningLightCounter2)) {
		startAnimation = false;
		setAllLEDs(off);
	}
	ws281x_send();
}

void nextStateLED(state_t nextStateLED) {
	if (nextStateLED == leds.state)
		return;

	if(leds.state == LED_STATE_COLOR_FADE){
		setAllLEDs(off);				 // Have to be done to reset the leds in the electronics room
		setBrightness(LED_BRIGHTNESS);	// Reset the brightness
	}

	leds.state = nextStateLED;
}

void nextState() {
	if(leds.state == LED_STATE_COLOR_FADE){
		leds.state = LED_STATE_OFF;
		setBrightness(LED_BRIGHTNESS);	// Reset the brightness
	} else
		leds.state++;
}
