/*
 * Timer.c
 *
 * Created: 8/26/2020 10:29:00 PM
 *  Author: ahmed
 */ 
#include "Timer.h"
#include <math.h>
//initial value given to register Timer_VALUE
//Timer_val is in hexadecimal
void Timer_init(uint32_t Timer_val){
	Timer_VALUE = Timer_val;
}
//starts the timer using Timer_CTRL register
//Timer_config is a hexadecimal value that sets the prescaler
void Timer_start(uint32_t Timer_config){
	Timer_CTRL = Timer_config;
}
// stops the timer using Timer_CTRL register
void Timer_stop(){
	Timer_CTRL = 0;
}
// sets the timer value to a certain time
void Timer_set_value(uint32_t value){
	Timer_VALUE = value;
}
// check if timer state reached the target or not yet
void Timer_get_state(uint32_t target ,uint8_t *flag){
	// loop to stay in the function until the timer reaches the target 
	while(1){
	// if timer reaches 0xff aka 255 and didn't reach the target , it will restart from 0.
	// so we handle this condition here
	if (Timer_VALUE == 0xff || Timer_VALUE == target){	
		if(target - Timer_VALUE >0){				// target is bigger than max value of timer
			Timer_set_value(0x00);					//restart the timer with a new target (-256)
			target -= 256;
		}else{										//else means the timer reached the target 
		*flag = 1;									//sets the flag to 1 and get out of the loop-->function
		break;
			}
		}
	}
}
