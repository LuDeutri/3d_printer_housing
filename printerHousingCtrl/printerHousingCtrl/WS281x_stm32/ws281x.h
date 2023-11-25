/*
 * This class handles WS281x led´s based on a stm32 processor with using PWM and DMA.
 * Based on the work of https://controllerstech.com/interface-ws2812-with-stm32/
 *
 * It is important to set the clock configuration in the .ioc, otherwise
 * it will not work.
 * If you are using an other clock speed, you have to calculate the new ARR for the timer which is used
 * for the PWM data signal and modify the defined constants below.
 *
 * Set the following settings in the ioc:
 *
 * System clock: 72 Mhz
 *
 * Timer
 * TIM Prescaler: 0
 * TIM ARR: 90-1     // ARR = Sys_clk / 800000
 *
 * DMA
 * Direction: Memory to Peripheral
 * Mode: Normal
 * Priority: Medium
 * Peripheral Increment Address: unchecked
 * Peripheral Data Width: Half Word
 * Memory Increment Address: checked
 * Memory Data Width: Byte
 */


#ifndef __ws281x
#define __ws281x

#include "../config.h"

// --------------- To set by user ---------------------------
// Here defined setttings are only used here and not written in the main.c
// You have to set the same adjustments in the .ioc

// In the WS2811 led strip are 3 leds controlled by one IC.
// In the WS2812 led strip every led has is one controller IC included.
#define USE_WS2811 1	// WS2811: 1 , WS2812: 0

//#define NUM_LED 				// Number of leds controlled by mcu 	//(NUM_LED defined in config.h)

#define SYS_CLK 72000000
#define TIMER &htim1
#define TIMER_CHANNEL TIM_CHANNEL_1
#define TIM_PRESCALER 0
#define TIM_ARR 90      // (SYS_CLK / TIM_ARR) = 800 kHz


// -------------- Dont´t modify lines below ----------------------------



#define USE_BRIGHTNESS 1
#define BRIGTHNESS_STANDART 40
#define PI 3.14159265

typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} color_t;

extern const color_t off;
extern const color_t red;
extern const color_t orange;
extern const color_t yellow;
extern const color_t green;
extern const color_t blue;
extern const color_t indigo;
extern const color_t violett;
extern const color_t white;

extern color_t colorFadeReg[];
extern size_t colorFadeRegSize;

extern color_t colorBlinkReg[];
extern size_t colorBlinkRegSize;

extern uint8_t numberLeds;

void ws281x_init();

/*
 * Translate RGB data into PWM duty cycle and start the DMA
 */
void ws281x_send();

/*
 * Set all led´s off
 */
void ws281x_settOff();

/*
 * Set the given led with the given RGB data. The led is not updated until ws281x_send() is called.
 * @param LEDnum number of the led which color is to set
 * @param red value for the red led brightness, 0-254
 * @param green value for the green led brightness, 0-254
 * @param blue value for the blue led brightness, 0-254
 */
void setLED(uint8_t LEDnum, color_t color);

/*
 * Set all LEDs which are controlled by this mcu
 * @param red value for the red led brightness, 0-254
 * @param green value for the green led brightness, 0-254
 * @param blue value for the blue led brightness, 0-254
 */
void setAllLEDs(color_t color);

/*
 * Set the brightness of the leds
 * @param brightness valid input 0-45 for the brightness of the leds
 */
void setBrightness(uint8_t br);
uint8_t getBrightness();

void calculateLedDataWithBrightness();


/*
 * HAL function overwrite to detect the end of the DMA conversation
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);

#endif
