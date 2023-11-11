#include "displayScreensaver.h"

screensaver_t screensaver;
uint32_t raspiIgnoreStartTime;

void screensaver_init(){
	screensaver.displayScreensaverActive = true;
	screensaver.ignoreRaspiInput = false;
	screensaver.raspiInput = false;
}

void screensaver_update(){
	// Reset ignore statemant after defined time if it is set to true
	if(screensaver.ignoreRaspiInput && HAL_GetTick() > raspiIgnoreStartTime + RESET_RASPI_DISPLAYSCREENSAVER_INPUT_IGNORE)
		screensaver.ignoreRaspiInput = false;

	// Toggle screensaver if the button is pressed
	if(getButtonState(BUTTON_DISPLAY))
		tooglDisplayScreensaver();

	// Set screensaver with raspi statement
	screensaver.displayScreensaverActive = screensaver.raspiInput;

	// Update screensaver output, here LOW activates the screensaver
	HAL_GPIO_WritePin(nScreensaver_GPIO_Port, nScreensaver_Pin, screensaver.displayScreensaverActive);
}

void tooglDisplayScreensaver(){
	screensaver.displayScreensaverActive ^= 1;
	screensaver.ignoreRaspiInput = true;
	raspiIgnoreStartTime = HAL_GetTick();
}

void setDisplayScreensaver(bool displayTimeout){
	screensaver.displayScreensaverActive = displayTimeout;
	screensaver.ignoreRaspiInput = true;
	raspiIgnoreStartTime = HAL_GetTick();
}
