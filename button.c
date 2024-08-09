#include "button.h"
#include "pwm.h"
#include "adc.h"
#include "stm32f303xe.h"

#define ZERO 0
#define HALF 512
#define FULL 1023

void EXTI0_IRQHandler(void)
{
	if (inADCMode == 0)
	{
		update_duty_cycle(ZERO);
	}
	EXTI -> PR |= EXTI_PR_PR0;
}

void EXTI1_IRQHandler(void)
{
	if (inADCMode == 0)
	{
		update_duty_cycle(HALF);
	}
	EXTI -> PR |= EXTI_PR_PR1;
}

void EXTI2_TSC_IRQHandler(void)
{
	if (inADCMode == 0)
	{
		update_duty_cycle(FULL);
	}
	EXTI -> PR |= EXTI_PR_PR2;
}

// ISR for button 3 (to enable/disable ADC mode)
void EXTI3_IRQHandler(void)
{
	if (!inADCMode)
	{
		// Enables ADC and blocks other buttons
		start_ADC1();
		inADCMode = 1;
	}
	else
	{
		// Disables ADC - control back to other buttons
		disable_ADC1();
		inADCMode = 0;
	}
	EXTI -> PR |= EXTI_PR_PR3;
}

// Sets up button 0
void setup_button_0(void)
{
	// Sets up PC0 as input
	RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC -> MODER &= ~(GPIO_MODER_MODER0_Msk);
	
	// Configures interrupt line for button
	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG -> EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI0_Msk);
	SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PC;
	
	// Sets up EXTI0 interrupt line
	EXTI -> IMR |= EXTI_IMR_MR0;
	EXTI -> FTSR |= EXTI_FTSR_FT0; // Set up to trigger on falling edge
	
	// Enable interrupt
	NVIC_EnableIRQ(EXTI0_IRQn);
}

// Sets up button 1
void setup_button_1(void)
{
	// Sets up PC1 as input
	RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC -> MODER &= ~(GPIO_MODER_MODER1_Msk);
	
	// Configures interrupt line for button
	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG -> EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI1_Msk);
	SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PC;
	
	// Sets up EXTI1 interrupt line
	EXTI -> IMR |= EXTI_IMR_MR1;
	EXTI -> FTSR |= EXTI_FTSR_FT1; // Set up to trigger on falling edge
	
	// Enable interrupt
	NVIC_EnableIRQ(EXTI1_IRQn);
}

// Sets up button 2
void setup_button_2(void)
{
	// Sets up PC2 as input
	RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC -> MODER &= ~(GPIO_MODER_MODER2_Msk);
	
	// Configures interrupt line for button
	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG -> EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI2_Msk);
	SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PC;
	
	// Sets up EXTI2 interrupt line
	EXTI -> IMR |= EXTI_IMR_MR2;
	EXTI -> FTSR |= EXTI_FTSR_FT2; // Set up to trigger on falling edge
	
	// Enable interrupt
	NVIC_EnableIRQ(EXTI2_TSC_IRQn);
}

// Sets up button 3
void setup_button_3(void)
{
	isADCMode = 0;
	
	// Sets up PC3 as input
	RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC -> MODER &= ~(GPIO_MODER_MODER3_Msk);
	
	// Configures interrupt line for button
	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG -> EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI3_Msk);
	SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PC;
	
	// Sets up EXTI2 interrupt line
	EXTI -> IMR |= EXTI_IMR_MR3;
	EXTI -> FTSR |= EXTI_FTSR_FT3; // Set up to trigger on falling edge
	
	// Enable interrupt
	NVIC_EnableIRQ(EXTI3_IRQn);
}
