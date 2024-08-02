#ifndef TIMER7_H
#define TIMER7_H

#include "stm32f303xe.h"

static volatile uint32_t counter; // Counter variable to keep track of timer ticks

void TIM7_IRQHandler(void); // ISR for TIM7 (iterates timer ticks)

void setup_TIM7(uint32_t prescaler, uint32_t count_freq); // Sets up and enables TIM7

#endif
