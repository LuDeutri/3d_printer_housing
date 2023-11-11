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

#include"../Core/Inc/main.h"

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
#define NUM_LED 141
#define NUM_LED_STRIP_BOTTOM_LEFT 15 	// In the electronics area under the printer
#define NUM_LED_STRIP_LEFT 36			// Left to the printer
#define NUM_LED_STRIP_TOP 39			// About the printer
#define NUM_LED_STRIP_RIGHT 16			// Right to the printer
#define NUM_LED_STRIP_BOTTOM_RIGHT 15	// In the electronics area under the printer
#define LED_BRIGHTNESS 255				// 0 ... 255
#define TIME_STARTING_ANIMATION 3000	// Duration of the start animation
#define ENABLE_START_ANIMATION 0

// Fire extinguisher
#define FIRE_EXTINGUISHER_TRIGGER_TIMER 20000 		// time until co2 valve is opening
#define FIRE_EXTINGUISHER_EXIT_BTN_PRESS_TIME 2000	// If the Btn is pressed over that limit during fire extinguisher is active, extinguisher will be stopped
#define ERR_DELAY_FIRE_DETECTED 2000
#define THRESHOLD_GAS_SENSOR_FIRE_DETECTED 100 		// TODO define fire detected threshold

// Beeper
#define TIME_REDUCE_BEEPER 300000 				// beeper will be reduced

// Display
#define RESET_RASPI_DISPLAYSCREENSAVER_INPUT_IGNORE 3000 // After this time, the pi can ctrl the screensaver again

extern const bool useAnalogGasValue;

// ########################################
// Software configuration end
// ########################################

