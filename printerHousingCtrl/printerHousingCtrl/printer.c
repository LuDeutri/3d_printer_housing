#include "printer.h"

printer_t printer;

void printer_init(){
	printer.splyCtrl = false;	// true: 3d printer supply is enabled
	printer.splyCtrlRaspiInput = false; // Read out in printerHousing.c
	printer.ingoreRaspiInput = false;  // In case of printerShutdown() is called, ignore raspi input

	// Enable the printer power supply
	HAL_GPIO_WritePin(printer_sply_ctrl_GPIO_Port, printer_sply_ctrl_Pin, LOW);
}

void printer_update(){
	// Ctrl sply via raspberry pi in normal operation
	if(!printer.ingoreRaspiInput)
		printer.splyCtrl = printer.splyCtrlRaspiInput;
	// Start printer if button is pressed
	if(getButtonState(BUTTON_PRINTER_SPLY))
		printer.splyCtrl = true;

	// Update output pin
	HAL_GPIO_WritePin(printer_sply_ctrl_GPIO_Port, printer_sply_ctrl_Pin, printer.splyCtrl);
}

void printerShutdown(){
	printer.splyCtrl = false;
	printer.ingoreRaspiInput = true;
}

void resetRaspiIgnoreStatement(){
	printer.ingoreRaspiInput = false;
}
