#include "timer7.h"

void TIM7_IRQHandler(void)
{
	counter++;
}

void setup_TIM7(uint32_t prescaler, uint32_t count_freq)
{
	// Enable clock
	RCC -> APB1ENR |= RCC_APB1ENR_TIM7EN; 
	
	// Set prescalar and auto-reload (to set up frequency)
	TIM7 -> PSC = prescaler;
	TIM7 -> ARR = (count_freq / prescaler);
	
	// Reset counter
	counter = 0;
	
	// Loads auto-reload register and enables update interrupt
	TIM7 -> CR1 |= TIM_CR1_ARPE;
	TIM7 -> DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM7_IRQn);
	
	// Enables TIM7
	TIM7 -> CR1 |= TIM_CR1_CEN;
}