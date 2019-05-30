#ifndef __ODOMETRY_H_
#define __ODOMETRY_H_


#include "main.h"
#include "arm_math.h"

#include "encoder.h"

typedef struct Odometry_S{
  Encoder encoder_l;
  Encoder encoder_r;
  volatile double x;
  volatile double y;
  volatile double theta;
  double speed_l;
  double speed_r;
  double speed_percent_tolerance;
}Odometry;

void init_odometry(Odometry *odometry, TIM_HandleTypeDef *htim_l, TIM_HandleTypeDef *htim_r, TIM_HandleTypeDef *htim_poll);

void update_odometry(Odometry *odometry);

#endif
