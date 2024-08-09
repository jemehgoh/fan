#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
 
// Time interval variables (for debouncing)
static volatile uint32_t prev_press_0;
static volatile uint32_t prev_press_1;
static volatile uint32_t prev_press_2;
static volatile uint32_t prev_press_3;

static volatile uint8_t inADCMode; // Variable to store whether fan is in ADC mode or not

// ISRs for external interrupts (buttons 1-4)
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_TSC_IRQHandler(void);
void EXTI3_IRQHandler(void);

// Setup functions for the four buttons (to be connected to PC0-PC4)
void setup_button_0(void);
void setup_button_1(void);
void setup_button_2(void);
void setup_button_3(void);

#endif
