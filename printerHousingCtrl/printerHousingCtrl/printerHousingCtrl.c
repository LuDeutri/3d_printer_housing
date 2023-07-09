#include "printerHousingCtrl.h"

bool printerSplyActive;
bool displayTimeout;

void printerHousingCtrl_init(){
	// Init variables
	printerSplyActive = true;
	displayTimeout = false;

	// Init modules
	button_init();
	fireExtinguisher_init();
	gasSensor_init();
	led_init();
}

void printerHousingCtrl_main(){

	// Wait for finished init
	if (clock() < 500)
		return;

	// Init variables
	printerHousingCtrl_init();

	// Main loop
	while(true){
		// Update inputs
		button_update();
		updatePiInput();

		// Update submodules
		gasSensor_update();
		fireExtinguisher_update();
		beeper_update();
		led_update();

		// Activate fire extinguisher sequence if fire is detected or the button is pressed
		if (getButtonState(BUTTON_FIRE_EXTINGUISHER) || gasSensor.fireDetected)
			fireExtinguisherStartCount();

		// Toggle debug led
		HAL_GPIO_WritePin(digMapPeriphal[DEBUG_LED], digMapChannel[DEBUG_LED], clock() % 1000 < 500);
	}
}

void updatePiInput(){
	// LED raspi pi inputs update
	uint8_t tmpDataInOne = HAL_GPIO_ReadPin(digMapPeriphal[LED_DATA_IN_ONE], digMapChannel[LED_DATA_IN_ONE]);
	uint8_t tmpDataInTwo = HAL_GPIO_ReadPin(digMapPeriphal[LED_DATA_IN_TWO], digMapChannel[LED_DATA_IN_TWO]);
	uint8_t tmpDataInThree = HAL_GPIO_ReadPin(digMapPeriphal[LED_DATA_IN_THREE], digMapChannel[LED_DATA_IN_THREE]);
#pragma warning(push, 0)
	leds.ledDataIn = (tmpDataInOne << 2) || (tmpDataInTwo << 1) || (tmpDataInThree);
#pragma warning(pop)

	// Printer supply input update
	printerSplyActive = HAL_GPIO_ReadPin(digMapPeriphal[PI_PRINTER_SPLY], digMapChannel[PI_PRINTER_SPLY]);
	// TODO Display timeout
}

void printerSupplyCtrl_update(){
	HAL_GPIO_WritePin(digMapPeriphal[PRINTER_SPLY_CTRL], digMapChannel[PRINTER_SPLY_CTRL], printerSplyActive);
}

void setPrinterSplyCtrl(bool splyCtrl){
	printerSplyActive = splyCtrl;
}

void toogleDisplayTimeout(){
	displayTimeout = !displayTimeout;
	HAL_GPIO_WritePin(digMapPeriphal[DISPLAY_TIMEOUT], digMapChannel[DISPLAY_TIMEOUT], displayTimeout);
}
