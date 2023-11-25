#include "led.h"

led_t leds;
clock_t startTimeTimeExpired;

bool startAnimation;

void led_init(){
	leds.ledDataIn = 0;
	leds.state = LED_STATE_WHITE;
	leds.ledPiDataUsed = false;
	leds.usedLedPiDataInput = LED_STATE_OFF;

	startAnimation = ENABLE_START_ANIMATION;

	startTimeTimeExpired = 0;

	ws281x_init();

}

void led_update() {
	// Start animation
	if(startAnimation)
		startAnimationLED();

	// Button ctrl, next state if button pressed
	if(getButtonState(BUTTON_LED))
		nextState();

	// Update LEDs depending on raspi pi data input
	if (leds.ledDataIn != leds.usedLedPiDataInput){
		leds.usedLedPiDataInput = leds.ledDataIn; 	// Store the data in usedDataInput to be sure its only one time updated with the same data
		nextState(leds.ledDataIn);
	}

	// Overwrite led status if fire is detected
	if(fireExtinguisher.activatingTime != 0)
		nextStateLED(LED_STATE_RED_FADE);

	//	TODO Statemachine for leds
	leds.state = LED_STATE_COLOR_BLINK;
	setBrightness(20);

	switch(leds.state){
	case LED_STATE_WHITE:
		setAllLEDs(white);
	break;
	case LED_STATE_GREEN:
		setAllLEDs(green);
	break;
	case LED_STATE_BLUE:
		setAllLEDs(blue);
	break;
	case LED_STATE_RED:
		setAllLEDs(red);
	break;
	case LED_STATE_GREEN_FADE:
		fadeOneColor(green);
	break;
	case LED_STATE_COLOR_BLINK:
		blinkColor(colorBlinkReg, colorBlinkRegSize);
		break;
	case LED_STATE_COLOR_FADE:
		fadeColorRegister(colorFadeReg, colorFadeRegSize);
		break;
	case LED_STATE_RED_FADE:
		//loopPulseColour(red);
	break;
	case LED_STATE_RAINBOW:
		//loopRainbow();
	break;
	case LED_STATE_OFF:
		//setWHOLEcolor(0,0,0);
	break;
	default:
		// You should never be here
	break;
	}
	// Update led string
	ws281x_send();
}

void startAnimationLED(){
	/*loopRunningLight(red, runningLightIndex1, 0, FORWARD);
	loopRunningLight(green, runningLightIndex2, NUM_LED/2, FORWARD);
	loopRunningLight(blue, runningLightIndex3, NUM_LED, BACKWARD);

	if(runningLightIndex1 >= NUM_LED-RUNNING_LIGHT_NUM_LEDS)
		startAnimation = false;
		*/
}

void nextStateLED(state_t nextStateLED) {
	if (nextStateLED == leds.state)
		return;

	leds.state = nextStateLED;
}

void nextState() {
	if(leds.state == LED_STATE_OFF)
		leds.state = LED_STATE_WHITE;
	else
		leds.state++;
}
