#include "printer.h"

printer_t printer;

void printer_init(){
	printer.splyCtrl = true;
	printer.splyCtrlRaspiInput = false;
	printer.ingoreRaspiInput = false;

	// Enable the printer power supply
	HAL_GPIO_WritePin(printer_sply_ctrl_GPIO_Port, printer_sply_ctrl_Pin, HIGH);
}

void printer_update(){
	// Ctrl sply via raspiberry pi in normal operation
	if(!printer.ingoreRaspiInput)
		printer.splyCtrl = printer.splyCtrlRaspiInput;


	if(HAL_GetTick() < 10000) // To ensure raspi has started completely
		return;
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
