/*
 * Timer.h
 *
 * Created: 8/26/2020 10:29:13 PM
 *  Author: ahmed
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include"../../utils/types.h"
#include "../../hardware/registers.h"

//set initial value for the timer
//Timer_val is in hexadecimal
void Timer_init(uint32_t Timer_val);
// starts the timer counter
// Timer_config is in hexadecimal
void Timer_start(uint32_t Timer_config);
// stops the timer using Timer_CTRL register
void Timer_stop();
//give value to timer to start from
void Timer_set_value(uint32_t value);
//check if the timer reached the target or not yet
void Timer_get_state(uint32_t target ,uint8_t *flag);
#endif /* TIMER_H_ */