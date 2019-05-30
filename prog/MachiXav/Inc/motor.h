#ifndef __motor_h
#define __motor_h

#include "main.h"

void setPWM(TIM_HandleTypeDef *timer, uint32_t channel, uint16_t period, uint16_t pulse);

void motorControl(TIM_HandleTypeDef * timer,int value,uint8_t ismLeft);

#endif