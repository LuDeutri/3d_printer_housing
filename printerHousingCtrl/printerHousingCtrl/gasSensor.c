#include "gasSensor.h"

gasSensor_t gasSensor;

void gasSensor_init(){
	gasSensor.fireDetected = false;
	gasSensor.fireDetectedTime = 0;
	gasSensor.gasSensAnalog = 0;
	gasSensor.gasSensDig = 0;
}

void gasSensor_update(){
	// Update data
	gasSensorReadData();

	// Handle data
	if ((gasSensor.gasSensDig && !ENABLE_ANALOG_GAS_VALUE) 			// Fire detected by the sensor
			|| (gasSensor.gasSensAnalog > THRESHOLD_GAS_SENSOR_FIRE_DETECTED && ENABLE_ANALOG_GAS_VALUE)) {
		if(gasSensor.fireDetectedTime == 0) // Safe time fire is detected
			gasSensor.fireDetectedTime = HAL_GetTick();
		else if(gasSensor.fireDetectedTime + ERR_DELAY_FIRE_DETECTED < HAL_GetTick()){ // Wait err_delay
			gasSensor.fireDetected = true;
			fireExtinguisherStartCount();			// Activate the fire extinguisher sequence
		}
	}
}

void gasSensorReadData(){
	if(HAL_GetTick() < 30000) // Wait 10 seconds to calibrate the sensor first
		return;

	gasSensor.gasSensDig = HAL_GPIO_ReadPin(gas_sens_digital_GPIO_Port, gas_sens_digital_Pin);

	if (ENABLE_ANALOG_GAS_VALUE){
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		gasSensor.gasSensAnalog = HAL_ADC_GetValue(&hadc1);
	}
}
