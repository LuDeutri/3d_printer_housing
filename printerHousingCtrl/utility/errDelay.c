/*
 * errDelay.c
 *
 *  Created on: May 4, 2024
 *      Author: lucad
 */
#include "errDelay.h"

void createErrDelay(errDelay_t* errDelay, clock_t timeout){
	errDelay->timeout = timeout;
	errDelay->errOccuredTime = 0;
}

bool checkErrDelay(errDelay_t* errDelay, bool error){
	// Check if errDelay was created correctly
	if(!error){ // Reset errDelay if error is false
		errDelay->errOccuredTime = 0;
		return false;
	} else {
		if (errDelay->errOccuredTime == 0) // Check if the error has already occurred and set the time
			errDelay->errOccuredTime = HAL_GetTick();
		else{
			if (HAL_GetTick() > errDelay->errOccuredTime + errDelay->timeout) // Check if error timeout has expired
				return true;
		}
	}
	return false;
}
