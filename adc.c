#include "adc.h"
#include "pwm.h"
#include "stm32f303xe.h"

// ISR for ADC1
void ADC1_2_IRQHandler(void)
{
	if (ADC1 -> ISR & ADC_ISR_ADRDY)
	{
		// Conversion start
		ADC1 -> CR |= ADC_CR_ADSTART;
		ADC1 -> ISR |= ADC_ISR_ADRDY;
	}
	
	if (ADC1 -> ISR & ADC_ISR_EOC)
	{
		// Updates PWM duty cycle based upon ADC value
		update_duty_cycle(ADC1 -> DR);
		ADC1 -> ISR |= ADC_ISR_EOC;
	}
}

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
}

// Function to set up ADC1
void setup_ADC1(void)
{
	RCC -> AHBENR |= RCC_AHBENR_ADC12EN; // Enable clock to ADC1
	ADC1 -> CR &= ~(ADC_CR_ADVREGEN); // Clear ADVREGEN bits
	ADC1 -> CR |= ADC_CR_ADVREGEN_0; // Enable voltage regulator
	
	// Waits for voltage regulator to start up
	// uint32_t curr = counter;
	for (int i = 0; i < 81; i++);
	
	ADC12_COMMON -> CCR |= ADC12_CCR_CKMODE_0;
	
	// Calibrates and starts up ADC1
	calibrate_ADC1();
	
	for (int k = 0; k < 5; k++);
	
	enable_ADC1();
}

uint32_t read_ADC1()
{
	// Enables ADC1 and waits for it to be ready
	ADC1 -> CR |= ADC_CR_ADEN;
	while((ADC1 -> ISR & ADC_ISR_ADRDY) != ADC_ISR_ADRDY);
	ADC1 -> CR |= ADC_CR_ADSTART; // Start conversion
	while (!(ADC1 -> ISR & ADC_ISR_EOC)); // Waits for conversion to be completed
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
		while (ADC1 -> CR & ADC_CR_ADSTP); // Waits for conversion to stop
	}
	
	ADC1 -> CR |= ADC_CR_ADDIS; // Disables ADC1
}

void start_ADC1(void)
{
	// Enable interrupts
	ADC1 -> IER |= ADC_IER_ADRDYIE;
	ADC1 -> IER |= ADC_IER_EOCIE;
	NVIC_EnableIRQ(ADC1_IRQn);
	
	// Enables ADC1
	ADC1 -> CR |= ADC_CR_ADEN;
}
