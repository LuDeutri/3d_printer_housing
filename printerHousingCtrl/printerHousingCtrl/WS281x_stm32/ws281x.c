#include "ws281x.h"

bool dataSentFlag; // True if DMA action is finished and the next one can start

uint8_t ledData[NUM_LED][3]; // Store led color data in RGB
uint8_t ledDataMod[NUM_LED][3];  // Used for brightness

uint8_t pwmData[PWM_DATA_ARR_LENGTH]; // Store led color and brightness data in bit format for the WS281x Led's

void ws281x_init(void) {
	dataSentFlag = 0;

	ws281x_reset();
	setAllLEDs(0,0,0);	// Init led data array
	setBrightness(BRIGTHNESS_STANDART);

}

void ws281x_send (void){
	uint16_t indx=0;
	uint32_t color;

	for (int i= 0; i<NUM_LED; i++){
		// Safe led data in color, depending if brightness ctrl is used or not
#if USE_BRIGHTNESS
		color = ((ledDataMod[i][1]<<16) | (ledDataMod[i][2]<<8) | (ledDataMod[i][3]));
#else
		color = ((ledData[i][1]<<16) | (ledData[i][2]<<8) | (ledData[i][3]));
#endif

		// Translate RGB data in binary format for WS281x leds
		// The clk configuration in the .ioc must be set to:   clk:72 Mhz, Arr: 90
		for (int i=23; i>=0; i--){
			if (color&(1<<i))
				pwmData[indx] = 60;		// 2/3 of 90 (SysClk:72MHz/ARR:90 --> TimerFreq:800kHz)
			else
				pwmData[indx] = 30;		// 1/3 of 90

			indx++;
		}
	}
	for (int i=0; i<50; i++){
			pwmData[indx] = 0;
			indx++;
		}

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, indx);
	while (!dataSentFlag){};
	dataSentFlag = 0;

	HAL_Delay(1);
	//delay_us(10);
}

void setLED(uint8_t LEDnum, uint8_t red, uint8_t green, uint8_t blue){
	ledData[LEDnum][0] = green;
	ledData[LEDnum][1] = blue;
	ledData[LEDnum][2] = red;
}

void setAllLEDs(uint8_t red, uint8_t green, uint8_t blue){
	for(uint8_t i = 0; i<NUM_LED;i++){
		setLED(i,red,green,blue);
	}
}

void setBrightness (uint8_t brightness){  // 0-45
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<NUM_LED; i++)
	{
		ledDataMod[i][0] = ledData[i][0];
		for (int j=0; j<3; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			ledDataMod[i][j] = (ledData[i][j])/(tan(angle));
		}
	}

#endif

}

void ws281x_reset(){
	for(int i=0; i<(PWM_DATA_ARR_LENGTH);i++){
		pwmData[i] = 0;
	}

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, PWM_DATA_ARR_LENGTH);
	while (!dataSentFlag){};
	dataSentFlag = 0;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
	dataSentFlag = 1;
}
