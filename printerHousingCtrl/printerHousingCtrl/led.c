#include "led.h"

led_t leds;
const colour_t red = {255, 0, 0};
const colour_t orange = {255, 127, 0};
const colour_t yellow = {255, 255, 0};
const colour_t green = {0, 255, 0};
const colour_t blue = {0, 0, 255};
const colour_t indigo = {46, 43, 95};
const colour_t violett = {136, 0, 255};
const colour_t white = {255, 255, 255};

colour_t rainbowColourArr[] = {red, orange, yellow, green, blue, indigo, violett};
uint8_t fadeBrightness;
bool fadeOut;
bool fadedOut;
uint8_t rainbowCounter;
uint8_t runningLightIndex1;
uint8_t runningLightIndex2;
uint8_t runningLightIndex3;
clock_t startTimeTimeExpired;
bool startAnimation;

void led_init(){
	leds.ledDataIn = 0;
	leds.state = LED_STATE_WHITE;
	leds.ledPiDataUsed = false;
	leds.usedLedPiDataInput = LED_STATE_OFF;

	fadeBrightness = 0;
	fadeOut = false;
	fadedOut = false;
	rainbowCounter = 0;
	runningLightIndex1 = 0;
	runningLightIndex2 = 0;
	runningLightIndex3 = 0;
	startAnimation = ENABLE_START_ANIMATION;

	startTimeTimeExpired = 0;

	//ws2812_init();

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
		//nextStateLED(LED_STATE_RED_FADE);

	//	TODO Statemachine for leds
	switch(leds.state){
	case LED_STATE_WHITE:
		setAllLeds(white.r, white.g, white.b);
	break;
	case LED_STATE_GREEN:
		setAllLeds(green.r, green.g, green.b);
	break;
	case LED_STATE_BLUE:
		setAllLeds(blue.r, blue.g, blue.b);
	break;
	case LED_STATE_RED:
		setAllLeds(red.r, red.g, red.b);
	break;
	case LED_STATE_GREEN_FADE:
		//loopPulseColour(green);
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
	WS2812_Send();
}

void startAnimationLED(){
	loopRunningLight(red, runningLightIndex1, 0, FORWARD);
	loopRunningLight(green, runningLightIndex2, NUM_LED/2, FORWARD);
	loopRunningLight(blue, runningLightIndex3, NUM_LED, BACKWARD);

	if(runningLightIndex1 >= NUM_LED-RUNNING_LIGHT_NUM_LEDS)
		startAnimation = false;
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

// Pulse one colour
void loopPulseColour(colour_t colour) {
  // FadeOut:
    // True = Brightness decreases
    // False = Brightness rises

  // Set fadeOut
  if(fadeBrightness <= 0){
    fadeOut = false;
    fadedOut = true;
    fadeBrightness = 0;
  } else if (fadeBrightness >= LED_BRIGHTNESS) {
    fadeOut = true;
    fadedOut = false;
    fadeBrightness = LED_BRIGHTNESS;
  }

  // Brightness rises
  if(!fadeOut){
   if(isTimeExpired(TIME_FADE)){
    if(fadeBrightness < LED_BRIGHTNESS * 0.95 && fadeBrightness > LED_BRIGHTNESS * 0.05)
    	fadeBrightness += 2;
    else fadeBrightness++;
   }
  }
  // Brightness decreases
  else {
    if(isTimeExpired(TIME_FADE)){
      if(fadeBrightness < LED_BRIGHTNESS * 0.95 && fadeBrightness > LED_BRIGHTNESS * 0.05)
    	  fadeBrightness -= 2;
      else fadeBrightness--;
    }
  }

  // TODO set brighthness fadeBrighntess
  setWHOLEcolor(colour.r, colour.g, colour.b);
}

void loopRainbow(){
	fill_rainbow(rainbowCounter);
	rainbowCounter++;
}

void loopRunningLight(colour_t colour, uint8_t runningLightIndex, uint8_t offset, int8_t direction){

	runningLight(colour, runningLightIndex + offset, direction);

	if(FORWARD){
		if(runningLightIndex >= NUM_LED - RUNNING_LIGHT_NUM_LEDS) return;
		runningLightIndex += RUNNING_LIGHT_NUM_LEDS;
	} else {
		if(runningLightIndex <= RUNNING_LIGHT_NUM_LEDS) return;
		runningLightIndex -= RUNNING_LIGHT_NUM_LEDS;
	}
}

void runningLight(colour_t colour, uint8_t index, int8_t direction){
	for(int i = index; i < index + (direction*RUNNING_LIGHT_NUM_LEDS); i=i+(1*direction)){
		//setLEDcolor(index, colour.r, colour.g, colour.b);
	}
}

bool isTimeExpired(uint32_t milliseconds) {
	clock_t endTime;

	// Set start und end time in the first method run
	if(startTimeTimeExpired == 0){
		startTimeTimeExpired = HAL_GetTick();
		endTime = startTimeTimeExpired + milliseconds * CLOCKS_PER_SEC / 1000;
	}

	// Proof if the time is expired
    if(HAL_GetTick() >= endTime){
    	startTimeTimeExpired = 0;	// Reset start time and return true
    	return true;
    }

    return false;	// Otherwise return false until the time is expired
}

void fill_rainbow(uint8_t counter){
	colour_t rainbowColour;

	for(uint8_t i=1; i < NUM_LED-RAINBOW_SAME_COLOUR_LEDS-1; i++){
		rainbowColour = rainbowColourArr[i % RAINBOW_NUM_COLOURS + counter];

		setLEDcolor(i+RAINBOW_SAME_COLOUR_LEDS-2,rainbowColour.r, rainbowColour.g, rainbowColour.b);
	}
}
