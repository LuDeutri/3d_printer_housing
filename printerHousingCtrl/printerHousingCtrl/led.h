#ifndef LED_H_
#define LED_H_

#include <ws281x_stm32/example.h>
#include "config.h"
#include "button.h"
#include "fireExtinguisher.h"

// Statemachine states of the led strip
typedef enum{
	LED_STATE_OFF,		// 000
	LED_STATE_WHITE,  	// 001
	LED_STATE_GREEN,	// 010
	LED_STATE_BLUE,		// 011
	LED_STATE_RED,		// 100
	LED_STATE_GREEN_FADE, // 101
	LED_STATE_RED_FADE,  // 110
	LED_STATE_COLOR_FADE	// 111
}state_t ;

typedef struct{
	uint8_t ledDataIn : 3;
	bool ledPiDataUsed;
	uint8_t usedLedPiDataInput;
	state_t state;
} led_t;
extern led_t leds;

void led_init();
void led_update();

void startAnimationLED();
void nextStateLED(state_t nextStateLED);
void nextState();



bool isTimeExpired(uint32_t milliseconds);



#endif
