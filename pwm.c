#include "pwm.h"
#include "stm32f303xe.h"

#define AUTO_RELOAD 1023 

void setup_TIM3(uint32_t prescaler)
{
	// Sets up PA6 (TIM3 Channel 1 output) to output a PWM signal
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA -> AFR[0] |= (2 << GPIO_AFRL_AFRL6_Pos); // Set to AF2 (TIM3 Channel 1 output)
	GPIOA -> MODER |= GPIO_MODER_MODER6_1; // Alternate function mode
	
	// Sets up TIM3 for centre-aligned PWM mode
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3 -> CR1 |= TIM_CR1_CMS;
	TIM3 -> CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1); // PWM mode 1 (0110)
	
	// Enables preloading for auto-reload and output compare values
	TIM3 -> CR1 |= TIM_CR1_ARPE;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC1PE;
	
	// TIM3 -> CCER &= ~(TIM_CCER_CC1P);
	TIM3 -> CCER |= TIM_CCER_CC1E;
	
	// Sets up prescalar and auto-reload value
	TIM3 -> PSC = prescaler;
	TIM3 -> ARR = AUTO_RELOAD;
}

void start_PWM(uint32_t duty_cycle)
{
	// Loads CCR1 register (PWM output comp value)
	TIM3 -> CCR1 = duty_cycle;
	TIM3 -> EGR |= TIM_EGR_UG;
	
	// Starts PWM output
	TIM3 -> CR1 |= TIM_CR1_CEN;
}

void update_duty_cycle(uint32_t duty_cycle)
{
	// Loads new output compare value
	TIM3 -> CCR1 = duty_cycle;
}
