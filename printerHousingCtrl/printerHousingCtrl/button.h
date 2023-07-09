#ifndef BUTTON_H_
#define BUTTON_H_

#include "config.h"

typedef struct{
	bool buttonLED;
	bool buttonFireExtinguisher;
	bool buttonDisplay;
	uint32_t buttonPressedStartTime;
	bool buttonAlreadyUsed;
} button_t;

void button_init();
void button_update();

void buttonReadState();

bool getButtonState(uint8_t button);
uint32_t getButtonPressedTime();

#endif
