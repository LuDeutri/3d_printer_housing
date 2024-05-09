#include "printerHousingCtrl.h"

errDelay_t raspiLedInputOne;
errDelay_t raspiLedInputTwo;
errDelay_t raspiLedInputThree;
errDelay_t raspiPrinterSplyCtrl;
errDelay_t raspiScreenSaverCtrl;

bool tmpDataInOne;
bool tmpDataInTwo;
bool tmpDataInThree;

void printerHousingCtrl_init(){

	createErrDelay(&raspiLedInputOne, 1500);
	createErrDelay(&raspiLedInputTwo, 1500);
	createErrDelay(&raspiLedInputThree, 1500);
	createErrDelay(&raspiPrinterSplyCtrl, 1500);
	createErrDelay(&raspiScreenSaverCtrl, 1500);

	tmpDataInOne = false;
	tmpDataInTwo = false;
	tmpDataInThree = false;

	// Init modules
	button_init();
	fireExtinguisher_init();
	gasSensor_init();
	led_init();
	printer_init();
}

void printerHousingCtrl_main(){

	// Wait for finished init
	if (HAL_GetTick() < 1000)
		return;

	// Main loop
	while(true){
		// Update inputs
		button_update();
		updatePiInput();

		// Update submodules
		gasSensor_update();
		fireExtinguisher_update();
		led_update();
		printer_update();

		// Toggle debug led
		HAL_GPIO_WritePin(debug_led_GPIO_Port, debug_led_Pin, HAL_GetTick() % 1000 < 500);
	}
}

void updatePiInput(){
	if(HAL_GetTick() < 10000) // To ensure raspi has started completely
		return;

	// Check if the changed value is constant
	if(checkErrDelay(&raspiLedInputOne, tmpDataInOne != HAL_GPIO_ReadPin(pi_led_data_1_GPIO_Port, pi_led_data_1_Pin)))
		tmpDataInOne = HAL_GPIO_ReadPin(pi_led_data_1_GPIO_Port, pi_led_data_1_Pin);
	if(checkErrDelay(&raspiLedInputTwo, tmpDataInTwo != HAL_GPIO_ReadPin(pi_led_data_2_GPIO_Port, pi_led_data_2_Pin)))
		tmpDataInTwo = HAL_GPIO_ReadPin(pi_led_data_2_GPIO_Port, pi_led_data_2_Pin);
	if(checkErrDelay(&raspiLedInputThree, tmpDataInThree != HAL_GPIO_ReadPin(pi_led_data_3_GPIO_Port, pi_led_data_3_Pin)))
		tmpDataInThree = HAL_GPIO_ReadPin(pi_led_data_3_GPIO_Port, pi_led_data_3_Pin);

	// LED raspi pi inputs update
	leds.ledDataIn = (tmpDataInOne << 2) | (tmpDataInTwo << 1) | (tmpDataInThree);

	// Printer supply input update
	if(checkErrDelay(&raspiPrinterSplyCtrl, printer.splyCtrlRaspiInput != HAL_GPIO_ReadPin(pi_printer_sply_ctrl_GPIO_Port, pi_printer_sply_ctrl_Pin)))
		printer.splyCtrlRaspiInput = HAL_GPIO_ReadPin(pi_printer_sply_ctrl_GPIO_Port, pi_printer_sply_ctrl_Pin);
}
