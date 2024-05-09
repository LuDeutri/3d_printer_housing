/*
 * errDelay.h
 *
 *  Created on: May 4, 2024
 *      Author: lucad
 */

#ifndef ERRDELAY_H_
#define ERRDELAY_H_

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

#include <stm32f1xx_hal.h>

typedef struct{
	bool errOccuredTime;
	clock_t timeout;
}errDelay_t;

void createErrDelay(errDelay_t* errDelay, clock_t timeout);

bool checkErrDelay(errDelay_t* errDelay, bool error);

#endif /* ERRDELAY_H_ */
