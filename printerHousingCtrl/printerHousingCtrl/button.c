#include "button.h"

static button_t buttons;


void button_init(){
	buttons.buttonFireExtinguisher = false;
	buttons.buttonLED = false;
	buttons.buttonPrinterSply = false;
	buttons.buttonPressedStartTime = 0;
	buttons.buttonAlreadyUsed = false;
}

void button_update(){
	buttonReadState();

	if((buttons.buttonPrinterSply || buttons.buttonFireExtinguisher || buttons.buttonLED))
		if (buttons.buttonPressedStartTime == 0)
			buttons.buttonPressedStartTime = HAL_GetTick();
		else
			buttons.buttonAlreadyUsed = true;
	else {
		buttons.buttonAlreadyUsed = false;
		buttons.buttonPressedStartTime = 0;
	}
}

void buttonReadState(){
	// If-else is used to skip the left buttons if one is pressed
#pragma warning(push, 0)
	if(buttons.buttonFireExtinguisher = !HAL_GPIO_ReadPin(btn_fire_ExGuisher_GPIO_Port, btn_fire_ExGuisher_Pin));
	else if(buttons.buttonLED = !HAL_GPIO_ReadPin(btn_led_GPIO_Port, btn_led_Pin));
	else buttons.buttonPrinterSply = !HAL_GPIO_ReadPin(btn_PrinterSply_GPIO_Port, btn_PrinterSply_Pin);
#pragma warning(pop)
}

bool getButtonState(buttons_t button){
	if(buttons.buttonAlreadyUsed)
		return false;

	switch(button){
	case BUTTON_FIRE_EXTINGUISHER:
		return buttons.buttonFireExtinguisher;
	case BUTTON_LED:
		return buttons.buttonLED;
	case BUTTON_PRINTER_SPLY:
		return buttons.buttonPrinterSply;
	default:
		// You should never be here
		return false;
	}
}

uint32_t getButtonPressedTime(){
	return HAL_GetTick() - buttons.buttonPressedStartTime;
}
