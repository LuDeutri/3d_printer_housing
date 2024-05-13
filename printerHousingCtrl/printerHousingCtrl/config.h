#pragma once

// Standard includes
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stddef.h>

#include "../utility/errDelay.h"

#include"../Core/Inc/main.h"
#include <stm32f1xx_hal.h>


// ########################################
// Software configuration start
// ########################################

// Valve state
#define OPENED 1
#define CLOSED 0
#define HIGH 1
#define LOW 0
#define FORWARD 1
#define BACKWARD -1

// LED strips
// #define NUM_LED defined in ws281.h
#define ENABLE_START_ANIMATION 1		// 0: start animation is disabled
#define LED_BRIGHTNESS 30				// 0 ... 45
#define TIME_STARTING_ANIMATION 3000	// max duration of the start animation

// Electronics room
#define INDEX_LED_STRIP_BOTTOM_LEFT 0	// Index of the first led of this strip
#define NUM_LED_STRIP_BOTTOM_LEFT 15 	// In the electronics area under the printer left side
#define LIGHT_TIME_ELECTRONICS_ROOM 20000	// Duration how long the light in the electronics room is active after pressing the light button

#define INDEX_LED_STRIP_BOTTOM_RIGHT 109 // Index of the first led of this strip
#define NUM_LED_STRIP_BOTTOM_RIGHT 15	// In the electronics area under the printer right side

// Printer room led 14 - 105
#define INDEX_LED_STRIP_LEFT 15 		// Index of the first led of this strip
#define NUM_LED_STRIP_LEFT 36			// Left to the printer

#define INDEX_LED_STRIP_TOP	51			// Index of the first led of this strip
#define NUM_LED_STRIP_TOP 39			// About the printer

#define INDEX_LED_STRIP_RIGHT 90		// Index of the first led of this strip
#define NUM_LED_STRIP_RIGHT 15			// Right to the printer

#define NUM_LED_PRINTER_ROOM NUM_LED_STRIP_LEFT+NUM_LED_STRIP_TOP+NUM_LED_STRIP_RIGHT

// Fire extinguisher
#define FIRE_EXTINGUISHER_TRIGGER_TIMER 20000 		// Time until co2 valve is opening
#define FIRE_EXTINGUISHER_EXIT_BTN_PRESS_TIME 1	// If the Btn is pressed over that limit during fire extinguisher is active, extinguisher will be stopped
#define ERR_DELAY_FIRE_DETECTED 2000

// Gas sensor
#define THRESHOLD_GAS_SENSOR_FIRE_DETECTED 1000 		// TODO define fire detected threshold for analog value
#define GAS_SENSOR_ADC &hadc1


// Beeper
#define TIME_REDUCE_BEEPER 120000 				// beeper will be reduced

// Gas sensor
extern ADC_HandleTypeDef hadc1;
#define ENABLE_ANALOG_GAS_VALUE 0 // 0: digital value is used, 1: analog value is used

// ########################################
// Software configuration end
// ########################################
