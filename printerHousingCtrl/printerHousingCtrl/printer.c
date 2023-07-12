#include "printer.h"

printer_t printer;

void printer_init(){
	printer.splyCtrl = true;
	printer.splyCtrlRaspiInput = false;
	printer.ingoreRaspiInput = false;
}

void printer_update(){
	// Ctrl sply via raspiberry pi in normal operation
	if(!printer.ingoreRaspiInput)
		printer.splyCtrl = printer.splyCtrlRaspiInput;

	// Update output pin
	// HIGH: active, LOW: NOT ACTIVE
	HAL_GPIO_WritePin(printer_sply_ctrl_GPIO_Port, printer_sply_ctrl_Pin, printer.splyCtrl);
}

void printerShutdown(){
	printer.splyCtrl = false;
	printer.ingoreRaspiInput = true;
}

void resetRaspiIgnoreStatement(){
	printer.ingoreRaspiInput = false;
}
