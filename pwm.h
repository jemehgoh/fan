#ifndef PWM_H
#define PWM_H

#include <stdint.h>

void setup_TIM3(uint32_t prescaler);
void start_PWM(uint32_t duty_cycle);
void update_duty_cycle(uint32_t duty_cycle);

#endif
