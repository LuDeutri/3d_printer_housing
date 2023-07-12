#ifndef BUTTON_H_
#define BUTTON_H_

#include "config.h"

typedef enum{
	BUTTON_DISPLAY,
	BUTTON_LED,
	BUTTON_FIRE_EXTINGUISHER
} buttons_t;

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

bool getButtonState(buttons_t button);
uint32_t getButtonPressedTime();

#endif
