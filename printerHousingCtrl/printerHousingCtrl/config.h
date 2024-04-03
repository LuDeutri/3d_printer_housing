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
#define LED_BRIGHTNESS 45				// 0 ... 45
#define TIME_STARTING_ANIMATION 3000	// max duration of the start animation

// Electronics room
#define INDEX_LED_STRIP_BOTTOM_LEFT 0	// Index of the first led of this strip
#define NUM_LED_STRIP_BOTTOM_LEFT 15 	// In the electronics area under the printer left side

#define INDEX_LED_STRIP_BOTTOM_RIGHT 106// Index of the first led of this strip
#define NUM_LED_STRIP_BOTTOM_RIGHT 15	// In the electronics area under the printer right side

// Printer room led 14 - 105
#define INDEX_LED_STRIP_LEFT 15 		// Index of the first led of this strip
#define NUM_LED_STRIP_LEFT 36			// Left to the printer

#define INDEX_LED_STRIP_TOP	51			// Index of the first led of this strip
#define NUM_LED_STRIP_TOP 39			// About the printer

#define INDEX_LED_STRIP_RIGHT 90		// Index of the first led of this strip
#define NUM_LED_STRIP_RIGHT 16			// Right to the printer

#define NUM_LED_PRINTER_ROOM NUM_LED_STRIP_LEFT+NUM_LED_STRIP_TOP+NUM_LED_STRIP_RIGHT

// Fire extinguisher
#define FIRE_EXTINGUISHER_TRIGGER_TIMER 20000 		// Time until co2 valve is opening
#define FIRE_EXTINGUISHER_EXIT_BTN_PRESS_TIME 2000	// If the Btn is pressed over that limit during fire extinguisher is active, extinguisher will be stopped
#define ERR_DELAY_FIRE_DETECTED 2000
#define THRESHOLD_GAS_SENSOR_FIRE_DETECTED 100 		// TODO define fire detected threshold for analog value

// Beeper
#define TIME_REDUCE_BEEPER 300000 				// beeper will be reduced

// Display
#define RESET_RASPI_DISPLAYSCREENSAVER_INPUT_IGNORE 3000 // After this time, the pi can ctrl the screensaver again

extern const bool useAnalogGasValue;

// ########################################
// Software configuration end
// ########################################
