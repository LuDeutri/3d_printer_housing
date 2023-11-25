#ifndef LED_H_
#define LED_H_

#include <WS281x_stm32/example.h>
#include "config.h"
#include "button.h"
#include "fireExtinguisher.h"

#define TIME_FADE 10
#define RAINBOW_SAME_COLOUR_LEDS 2
#define RAINBOW_NUM_COLOURS 7
#define RUNNING_LIGHT_NUM_LEDS 1

// Statemachine states of the led strip
typedef enum{
	LED_STATE_WHITE,  	// 000
	LED_STATE_GREEN,	// 001
	LED_STATE_BLUE,		// 010
	LED_STATE_RED,		// 011
	LED_STATE_GREEN_FADE, // 100
	LED_STATE_COLOR_FADE,
	LED_STATE_COLOR_BLINK,
	LED_STATE_RED_FADE,  // 101
	LED_STATE_RAINBOW,	// 110
	LED_STATE_OFF		// 111
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
