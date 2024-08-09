#include "pwm.h"
#include "button.h"
#include "timer7.h"
#include "adc.h"

int main()
{
	__disable_irq();
	
	// PWM setup
	setup_TIM3(64);
	start_PWM(500);
	
	// ADC setup
	setup_ADC1();
	
	// Button setup
	setup_button_0();
	setup_button_1();
	setup_button_2();
	setup_button_3();
	
	__enable_irq();
	
	while (1)
	{
		
	}
	/*
	int counter = 0;
	uint32_t duty_cycle = 100;

	while (1)
	{
		counter++;
		duty_cycle++;
		update_duty_cycle(duty_cycle);
		if (duty_cycle > 800)
		{
			duty_cycle = 100;
		}
	}
	*/
}
