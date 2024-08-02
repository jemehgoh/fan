#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void calibrate_ADC1(void); // Calibrates ADC1
void enable_ADC1(void); // Starts ADC1 on channel 1
uint32_t read_ADC1(void); // Gets reading from ADC1
void disable_ADC1(void); // Disables ADC1

#endif
