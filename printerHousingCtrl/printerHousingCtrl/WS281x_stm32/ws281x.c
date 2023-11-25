#include "ws281x.h"

bool dataSentFlag; // True if DMA action is finished and the next one can start

uint8_t ledData[NUM_LED][3]; // Store led color data in RGB
uint8_t pwmData[PWM_DATA_ARR_LENGTH]; // Store led color and brightness data in bit format for the WS281x Led's


void ws281x_init(void) {
	dataSentFlag = 0;

	setAllLEDs(0,0,0);	// Init led data array
	ws281x_send();
}

void ws281x_send (void){
	uint16_t indx=0;
	uint32_t color;

	for (int i= 0; i<NUM_LED; i++){
		// Safe led data in color, depending if brightness ctrl is used or not
		color = ((ledData[i][0]<<16) | (ledData[i][1]<<8) | (ledData[i][2]));

		// Translate RGB data in binary format for WS281x leds
		// The clk configuration in the .ioc must be set to:   clk:72 Mhz, Arr: 90
		for (int i=23; i>=0; i--){
			if (color&(1<<i))
				pwmData[indx] = 48;		// 2/3 of 90 (SysClk:72MHz/ARR:90 --> TimerFreq:800kHz)
			else
				pwmData[indx] = 18;		// 1/3 of 90

			indx++;
		}
	}
	pwmData[indx] = 0; // Reset period with Delay minimum 270 us

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, indx);
	while (!dataSentFlag){};
	dataSentFlag = 0;

	HAL_Delay(1); // Delay for reset period

}

void setLED(uint8_t LEDnum, uint8_t red, uint8_t green, uint8_t blue){
	ledData[LEDnum][0] = blue;
	ledData[LEDnum][1] = red;
	ledData[LEDnum][2] = green;
}

void setAllLEDs(uint8_t red, uint8_t green, uint8_t blue){
	for(uint8_t i = 0; i<NUM_LED;i++)
		setLED(i,red,green,blue);
}

void ws281x_reset(){
	for(int i=0; i<(PWM_DATA_ARR_LENGTH);i++)
		pwmData[i] = 0;

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, PWM_DATA_ARR_LENGTH);
	while (!dataSentFlag){};
	dataSentFlag = 0;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
	dataSentFlag = 1;
}
