#ifndef GASSENSOR_H_
#define GASSENSOR_H_

/*
 * Gas sensor hardware: MQ-2 module
 * That module gives out an analog value for the gas concentration and a digital value
 * which is LOW in no error case and HIGH if an specific value is exceeded. This value
 * can be configured with a poti on the module pcb
 */

#include "config.h"
#include "fireExtinguisher.h"

typedef struct{
	float gasSensAnalog;
	bool gasSensDig;
	bool fireDetected;
	uint32_t fireDetectedTime;
} gasSensor_t;
extern gasSensor_t gasSensor;


void gasSensor_init();
void gasSensor_update();

void gasSensorReadData();



#endif
