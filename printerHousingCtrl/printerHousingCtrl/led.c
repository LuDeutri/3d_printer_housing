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


	//	TODO ----------- test circuit
	leds.state = LED_STATE_GREEN_FADE;
	//setBrightness(20);
	// TODO --------------test circuit end

	// Reset stored led data first
	//setAllLEDs(off);

	switch(leds.state){
	case LED_STATE_OFF:
		setAllLEDs(off);
	break;
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
		fadeOneColor(green, INDEX_LED_STRIP_LEFT, NUM_LED_PRINTER_ROOM);
	break;
	case LED_STATE_RED_FADE:
		fadeOneColor(red, INDEX_LED_STRIP_LEFT, NUM_LED_PRINTER_ROOM);
	break;
	case LED_STATE_RAINBOW:
		rainbow();
	break;
	// -------TODO test cycle ------
	case LED_STATE_COLOR_BLINK:
		blinkColors(colorBlinkReg, colorBlinkRegSize, 0, 5);
		break;
	case LED_STATE_COLOR_FADE:
		fadeColors(colorFadeReg, colorFadeRegSize, 0, 1);
		break;
	default:
		// You should never be here
	break;
	}
	// Update led string
	ws281x_send();
}

void startAnimationLED(){
	// Set start animation to finished if one running light cylce reach the end
	if(runningLight(red, 0, FORWARD) || runningLight(blue, NUM_LED, BACKWARD))
		startAnimation = false;
}

void nextStateLED(state_t nextStateLED) {
	if (nextStateLED == leds.state)
		return;

	leds.state = nextStateLED;
}

void nextState() {
	if(leds.state == LED_STATE_RAINBOW)
		leds.state = LED_STATE_OFF;
	else
		leds.state++;
}
