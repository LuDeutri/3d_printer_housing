#ifndef CONFIG_H_
#define CONFIG_H_

// Standard includes
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <stm32f1xx_hal.h>

// ########################################
// Hardware configuration
// ########################################

extern  GPIO_TypeDef* digMapPeriphal[];
extern  uint8_t digMapChannel[];

// Constants for mapping the physical name to logical digital channel.
#define DIGITAL_PA1 0
#define DIGITAL_PA2 1
#define DIGITAL_PA3 2
#define DIGITAL_PA4 3
#define DIGITAL_PA5 4
#define DIGITAL_PA6 5
#define DIGITAL_PA7 6
#define DIGITAL_PA8 7
#define DIGITAL_PA9	8
#define DIGITAL_PA10 9
#define DIGITAL_PA11 10
#define DIGITAL_PA12 11
#define DIGITAL_PA13 12
#define DIGITAL_PC13 13

// Name digital pins
#define LED_DATA_IN_ONE				DIGITAL_PA1
#define LED_DATA_IN_TWO				DIGITAL_PA2
#define LED_DATA_IN_THREE			DIGITAL_PA3
#define LED_DATA_OUT				DIGITAL_PA4
#define PI_PRINTER_SPLY				DIGITAL_PA12
#define PRINTER_SPLY_CTRL			DIGITAL_PA11
#define DISPLAY_TIMEOUT				DIGITAL_PA13
#define BUTTON_LED_CTRL				DIGITAL_PA5
#define BUTTON_FIRE_EXTINGUISHER	DIGITAL_PA6
#define BUTTON_DISPLAY				DIGITAL_PA10
#define VAVLE_FIRE_EXTINGUISHER		DIGITAL_PA8
#define BEEPER						DIGITAL_PA9
#define GAS_SENSOR_DIGIT_INPUT		DIGITAL_PA7
#define DEBUG_LED					DIGITAL_PC13

// ########################################
// Hardware configuration end
// ########################################


// ########################################
// Software configuration start
// ########################################

// Valve state
#define OPENED 1
#define CLOSED 0
#define HIGH 1
#define LOW 0
#define FORWARD 1
#define BACKWARD 0

#define NUM_LED 60
#define FIRE_EXTINGUISHER_TRIGGER_TIMER 10000 	// time until co2 valve is opening
#define FIRE_EXTINGUISHER_EXIT_BTN_PRESS_TIME 2000	// If the Btn is pressed over that limit during fire extinguisher is active, one will be stopped
#define ERR_DELAY_FIRE_DETECTED 2000
#define THRESHOLD_GAS_SENSOR_FIRE_DETECTED 100 	// TODO define fire detected threshold
#define TIME_REDUCE_BEEPER 300000 				// 5 minutes beeper will be reduced
#define LED_BRIGHTNESS 255				// 0 ... 255
#define TIME_STARTING_ANIMATION 3000	// Duration if the start animation of the leds

extern const bool useAnalogGasValue;

// ########################################
// Software configuration end
// ########################################

#endif
