/*
 * LED toggle.c
 * Created: 8/17/2020 12:27:39 PM
 * Author : Ahmed
 */
#include "hardware/registers.h"
#include "MCAL/DIO_Driver/DIO.h"
#include "MCAL/Timer_Driver/Timer.h"
// configuration array 8x4 that specifies whether the pin will be input "in" or output "out"
// Note: default is 0 which is the same as input "in"
uint8_t configuration [no_of_registers][no_of_pins] = {{0,0,0,0,0,0,0,0},		//A
													   {out,0,0,0,0,0,0,0},		//B
													   {0,0,0,0,0,0,0,0},		//C
													   {0,0,0,0,0,0,0,0}};		//D
							
int main(void)
{	//creating flags to indicate button state and LED state
	uint8_t button_state, LED_flag = 0;
	//setting LED times off and on (in ms)
	uint32_t LED_on_time = 300, LED_off_time = 500;
	// setting the timer conditions, timer initial value, and its configuration
	uint32_t Timer_init_val = 0x00, Timer_config = 0x05;
	//setting pins configuration
	DIO_init(configuration);
	//initializing the timer value
	Timer_init(Timer_init_val);
	//Application main loop
 while (1) 
    {	// checks if button is pressed or not
		DIO_read('C',pin_zero, &button_state);
		// while here means that as long as the button is being pressed
		while(button_state == 1){
			// starts the timer and sets the prescaler 
			Timer_start(Timer_config);
			// toggle LED on
			DIO_write('B',pin_zero,1);
			//check if timer reached the LED on max time or not yet
			Timer_get_state(LED_on_time,&LED_flag);
			if(LED_flag != 0){				//LED reached max LED on time
				LED_flag = 0;				//reset it to zero
				Timer_set_value(0x00);		//reset the timer to zero
				DIO_write('B',pin_zero,0);	//toggle LED off
				//check if timer reached the LED on max time or not yet
				Timer_get_state(LED_off_time,&LED_flag);
			}
			// checks button state
			DIO_read('C',pin_zero, &button_state);		
		}
		// out of button pressed loop resets the LED to off
		DIO_write('B',pin_zero,0);
	}
}

