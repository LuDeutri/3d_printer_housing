#include "button.h"

static button_t buttons;


void button_init(){
	buttons.buttonFireExtinguisher = false;
	buttons.buttonLED = false;
	buttons.buttonDisplay = false;
	buttons.buttonPressedStartTime = 0;
	buttons.buttonAlreadyUsed = false;
}

void button_update(){
	buttonReadState();

	if((buttons.buttonDisplay || buttons.buttonFireExtinguisher || buttons.buttonLED))
		if (buttons.buttonPressedStartTime == 0)
			buttons.buttonPressedStartTime = clock();
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
	if(buttons.buttonFireExtinguisher = HAL_GPIO_ReadPin(digMapPeriphal[BUTTON_FIRE_EXTINGUISHER], digMapChannel[BUTTON_FIRE_EXTINGUISHER]));
	else if(buttons.buttonLED = HAL_GPIO_ReadPin(digMapPeriphal[BUTTON_LED_CTRL], digMapChannel[BUTTON_LED_CTRL]));
	else buttons.buttonDisplay = HAL_GPIO_ReadPin(digMapPeriphal[BUTTON_DISPLAY], digMapChannel[BUTTON_DISPLAY]);
#pragma warning(pop)
}

bool getButtonState(uint8_t button){
	if(buttons.buttonAlreadyUsed)
		return false;

	switch(button){
	case BUTTON_FIRE_EXTINGUISHER:
		return buttons.buttonFireExtinguisher;
	case BUTTON_LED_CTRL:
		return buttons.buttonLED;
	case BUTTON_DISPLAY:
		return buttons.buttonDisplay;
	default:
		// You should never be here
		return false;
	}
}

uint32_t getButtonPressedTime(){
	return clock() - buttons.buttonPressedStartTime;
}
