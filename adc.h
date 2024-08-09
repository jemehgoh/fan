#ifndef ADC_H
#define ADC_H

#include <stdint.h>

//static volatile uint32_t holder = 500;

void ADC1_2_IRQHandler(void);

void calibrate_ADC1(void); // Calibrates ADC1
void enable_ADC1(void); // Sets up ADC1 on channel 1
void setup_ADC1(void); // Calibrates and sets up ADC1
uint32_t read_ADC1(void); // Gets reading from ADC1
void disable_ADC1(void); // Disables ADC1
void start_ADC1(void); // Starts ADC on channel 1

#endif
