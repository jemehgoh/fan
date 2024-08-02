#include "adc.h"
#include "stm32f303xe.h"

// Calibrates ADC1
void calibrate_ADC1(void)
{
	ADC1 -> CR &= ~(ADC_CR_ADEN); // Ensures ADC1 is disabled
	ADC1 -> CR &= ~(ADC_CR_ADCALDIF); // Single input mode
	
	ADC1 -> CR |= ADC_CR_ADCAL; // Start calibration
	while ((ADC1 -> CR & ADC_CR_ADCAL) == ADC_CR_ADCAL); // Polls ADCAL bit until conversion completed
}

void enable_ADC1()
{
	// Sets up PA0 (ADC1_IN0) for analog (ADC input)
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA -> MODER |= GPIO_MODER_MODER0;
	
	// Set up channel 
	ADC1 -> CFGR |= ADC_CFGR_CONT;
	ADC1 -> SQR1 |= ADC_SQR1_SQ1_0;
	
	// Enable interrupts
	ADC1 -> IER |= ADC_IER_ADRDYIE;
	ADC1 -> IER |= ADC_IER_EOCIE;
	NVIC_EnableIRQ(ADC1_IRQn);
}

uint32_t read_ADC1()
{
	// Enables ADC1 and waits for it to be ready
	ADC1 -> CR |= ADC_CR_ADEN;
	while((ADC1 -> ISR & ADC_ISR_ADRDY) != ADC_ISR_ADRDY);
	ADC1 -> CR |= ADC_CR_ADSTART; // Start conversion
	while (ADC1 -> ISR & ADC_ISR_EOC); // Waits for conversion to be completed
	ADC1 -> ISR |= ADC_ISR_EOS;
	ADC1 -> ISR |= ADC_ISR_EOC;
	uint32_t out = ADC1 -> DR;
	disable_ADC1();
	return out;
}

// Disables ADC1 and stops any ongoing conversions
void disable_ADC1()
{
	// Disables any ongoing conversions 
	if (ADC1 -> CR & ADC_CR_ADSTART)
	{
		ADC1 -> CR |= ADC_CR_ADSTP;
		while (ADC1 -> CR & ADC_CR_ADSTP); // Waaits for conversion to stop
	}
	
	ADC1 -> CR |= ADC_CR_ADDIS; // Disables ADC1
}
