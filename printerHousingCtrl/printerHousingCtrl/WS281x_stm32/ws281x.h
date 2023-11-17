#ifndef __ws281x
#define __ws281x

#include "../config.h"
#include "../hal_delay.h"
#include "../../Core/Inc/main.h"

//#define NUM_LED 				NUM_LED defined in config.h
#define USE_BRIGHTNESS 0
#define BRIGTHNESS_STANDART 40
#define PWM_DATA_ARR_LENGTH ((24*NUM_LED)+50) // 24Bits per LED + 40x 0 for reset cycle

#define PI 3.14159265

void ws281x_init();
void ws281x_send();

void setLED(uint8_t LEDnum, uint8_t red, uint8_t green, uint8_t blue);
void setAllLEDs(uint8_t red, uint8_t green, uint8_t blue);
void setBrightness (uint8_t brightness);

void ws281x_reset();


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);

#endif
