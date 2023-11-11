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
	if (useAnalogGasValue){
		// TODO Gas Sensor analog bewerten
		// THRESHOLD_GAS_SENSOR_FIRE_DETECTED
	} else if (gasSensor.gasSensDig)
		gasSensor.fireDetected = true;

	// Activate fire extinguisher after a defined error delay
	if(gasSensor.fireDetected && gasSensor.fireDetectedTime + ERR_DELAY_FIRE_DETECTED > HAL_GetTick())
		fireExtinguisherActivate();
}

void gasSensorReadData(){
	gasSensor.gasSensDig = HAL_GPIO_ReadPin(gas_sens_digital_GPIO_Port, gas_sens_digital_Pin);

	if (useAnalogGasValue){
		// TODO Read out analog data of gas sensor
	}
}
