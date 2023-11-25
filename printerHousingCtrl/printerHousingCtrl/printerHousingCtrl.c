#include "printerHousingCtrl.h"

bool printerSplyActive;
bool raspiPrinterSplyInput;

void printerHousingCtrl_init(){
	// Init variables
	printerSplyActive = true;
	raspiPrinterSplyInput = true;

	// Init modules
	button_init();
	fireExtinguisher_init();
	gasSensor_init();
	led_init();
	screensaver_init();
	printer_init();

	//HAL_TIM_Base_Start(&TIM_HAL_DELAY); // Start us delay timer
}

void printerHousingCtrl_main(){

	// Wait for finished init
	//if (HAL_GetTick() < 500)
		//return;

	// Main loop
	while(true){
		// Update inputs
		//button_update();
		//updatePiInput();

		// Update submodules
		//gasSensor_update();
		//fireExtinguisher_update();
		//beeper_update();
		led_update();
		//screensaver_update();
		printer_update();

		// Activate fire extinguisher sequence if fire is detected or the button is pressed
		if (getButtonState(BUTTON_FIRE_EXTINGUISHER) || gasSensor.fireDetected)
			fireExtinguisherStartCount();

		// Toggle debug led
		HAL_GPIO_WritePin(debug_led_GPIO_Port, debug_led_Pin, HAL_GetTick() % 1000 < 500);
	}
}

void updatePiInput(){
	// LED raspi pi inputs update
	uint8_t tmpDataInOne = HAL_GPIO_ReadPin(pi_led_data_1_GPIO_Port, pi_led_data_1_Pin);
	uint8_t tmpDataInTwo = HAL_GPIO_ReadPin(pi_led_data_2_GPIO_Port, pi_led_data_2_Pin);
	uint8_t tmpDataInThree = HAL_GPIO_ReadPin(pi_led_data_3_GPIO_Port, pi_led_data_3_Pin);
//#pragma warning(push, 0)
	leds.ledDataIn = (tmpDataInOne << 2) | (tmpDataInTwo << 1) | (tmpDataInThree);
//#pragma warning(pop)

	// Printer supply input update
	printer.splyCtrlRaspiInput = HAL_GPIO_ReadPin(pi_printer_sply_ctrl_GPIO_Port, pi_printer_sply_ctrl_Pin);
	screensaver.raspiInput = HAL_GPIO_ReadPin(pi_displayScreensaver_GPIO_Port, pi_displayScreensaver_Pin);
}
