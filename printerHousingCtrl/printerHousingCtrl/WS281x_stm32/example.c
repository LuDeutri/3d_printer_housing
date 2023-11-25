#include "example.h"


uint32_t blinkTime = 0;
uint8_t blinkIndex = 0;
void blinkColor(color_t* color, size_t size){
	setAllLEDs(color[blinkIndex]);	// Set LEDs

	if(HAL_GetTick() > blinkTime + BLINK_TIME){ // Set next color after BLINK_TIME
		blinkIndex++;
		blinkTime = HAL_GetTick();

		if(blinkIndex >= size) // Reset if all colors were shown
			blinkIndex = 0;
	}
}


bool fadeIn = false;
uint32_t fadeTime = 0;
void fadeOneColor(color_t color) {
	setAllLEDs(color);

	// If brigthness ctrl is deactivated, set all leds to the given color and stop the method
	if(!USE_BRIGHTNESS)
		return;

	uint8_t tmpBrightness = getBrightness();

	if(tmpBrightness <= 0)	// start fading in if min brightness is reached
		fadeIn = true;
	else if(tmpBrightness >=45)	// end fading in if max brightness is reached
		fadeIn = false;

	// Wait with the next fade sequence
	if(HAL_GetTick() < fadeTime + FADE_TIME)
		return;

	if(tmpBrightness > 0 && !fadeIn)		// fade out
		setBrightness(tmpBrightness-1);
	else if(tmpBrightness < 45 && fadeIn)	// fade in
		setBrightness(tmpBrightness+1);

	fadeTime = HAL_GetTick();
}


uint8_t colorIndex = 0;
void fadeColorRegister(color_t* color, size_t size){
	uint8_t tmpBrightness = getBrightness();

	if(tmpBrightness <= 0 && !fadeIn)	// Change the color if the brightness is set to 0
		colorIndex++;
	if(colorIndex >= size)	// Restart if all colors were faded
		colorIndex = 0;

	fadeOneColor(color[colorIndex]); // Fade one color
}

/*
color_t colorRainbowReg[] = { red, orange, yellow, green, blue, indigo, violett };
size_t colorRainbowRegSize = sizeof(colorRainbowReg)/sizeof(colorRainbowReg[0]);
void rainbow(){

	for(uint8_t i=0; i < ((numberLeds-1)-RAINBOW_LED_SAME_COLOR); i++){
		colorRainbowReg = colorRainbowReg[i % RAINBOW_NUM_COLOURS + counter];

		setLED(i+RAINBOW_LED_SAME_COLOR-2,rainbowColour.r, rainbowColour.g, rainbowColour.b);
	}
}



void runningLight(colour_t colour, uint8_t index, int8_t direction){
	for(int i = index; i < index + (direction*RUNNING_LIGHT_NUM_LEDS); i=i+(1*direction)){
		//setLEDcolor(index, colour.r, colour.g, colour.b);
	}
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



*/
