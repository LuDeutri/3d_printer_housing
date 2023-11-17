#include "hal_delay.h"


void delay_us (uint16_t us){
	__HAL_TIM_SET_COUNTER(&TIM_HAL_DELAY,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&TIM_HAL_DELAY) < us);  // wait for the counter to reach the us input in the parameter
}
