/*
 * Contains led light simulation examples
 */

#include "ws281x.h"

#ifndef WS281X_STM32_EXAMPLE_H_
#define WS281X_STM32_EXAMPLE_H_

#define BLINK_TIME 500
#define FADE_TIME 30

#define RAINBOW_LED_SAME_COLOR 2

void blinkColor(color_t* color, size_t size);
void fadeOneColor(color_t);
void fadeColorRegister(color_t color[], size_t size);

void rainbow();


#endif
