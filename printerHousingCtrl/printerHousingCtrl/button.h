#ifndef BUTTON_H_
#define BUTTON_H_

#include "config.h"

typedef enum{
	BUTTON_LED,
	BUTTON_PRINTER_SPLY,
	BUTTON_FIRE_EXTINGUISHER
} buttons_t;

typedef struct{
	bool buttonLED;
	bool buttonFireExtinguisher;
	bool buttonPrinterSply;
	uint32_t buttonPressedStartTime;
	bool buttonAlreadyUsed;
} button_t;

void button_init();
void button_update();

/*
 * Read the button states, if one is true, skip the other.
 */
void buttonReadState();

/*
 * Return button state
 * @return button state
 */
bool getButtonState(buttons_t button);

/*
 * Return the time the button is pressed
 * @return time button is pressed
 */
uint32_t getButtonPressedTime();

#endif
