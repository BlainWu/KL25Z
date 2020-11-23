#ifndef _PWMLED_H
#define _PWMLED_H

#include "MKL25Z4.h"

void pwmled_init();
void pwmled_set(uint16_t duty_cycle,uint8_t colour);

#endif