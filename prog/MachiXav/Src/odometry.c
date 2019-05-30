#include "odometry.h"
#include "usart.h"

volatile float ENCODER_DIST=190.66;//distance between encoders
volatile float ENCODER_STEP_DIST=/* 20.65 */6.24*2/6.0*2*M_PI/1440.0; //distance for 1 encoder step SAME
volatile float deltaL=(20.65*2*M_PI/1440.0)/199.66; //ENCODER_STEP_DIST/ENCODER_DIST
int max;
void update_odometry(Odometry *odometry){
    //this can look like an error but due to technical specification it is like that
    int dl_l = update_encoder(&odometry->encoder_r);
    int dl_r = -update_encoder(&odometry->encoder_l);

/*      int n;char buffer[80];
    HAL_UART_Transmit(&huart2,"                         ",25,10);
    n = sprintf(buffer, "\r%d : ",(int)(odometry->y*100));
    HAL_UART_Transmit(&huart2,buffer,n,10);
     
    n = sprintf(buffer, "%d\r",(int)(odometry->x*100));
    HAL_UART_Transmit(&huart2,buffer,n,10); */

#if TEST_ENCODER==1
  led_level = (int) (((float) odometry->encoder_l.htim->Instance->CNT / ENCODER_MAX)*255);
#endif

#if TEST_ENCODER==2
  led_level = (int) (((float) odometry->encoder_r.htim->Instance->CNT / ENCODER_MAX)*255);
#endif


  odometry->x = odometry->x
    + cos(odometry->theta)*ENCODER_STEP_DIST*(dl_l + dl_r);

  odometry->y = odometry->y
    + sin(odometry->theta)*ENCODER_STEP_DIST*(dl_l + dl_r);

  odometry->theta = odometry->theta+deltaL*(dl_l - dl_r);

  if(odometry->theta>PI)//angle limitation to -PI +PI
  {
    odometry->theta=odometry->theta-2*PI;
  }
  else if(odometry->theta<=-PI)
  {
    odometry->theta=odometry->theta+2*PI;
  }
}

void init_odometry(Odometry *odometry, TIM_HandleTypeDef *htim_l, TIM_HandleTypeDef *htim_r, TIM_HandleTypeDef *htim_poll){
  odometry->x = odometry->y = 0;
  odometry->theta = 0;

  init_encoder(&odometry->encoder_l,htim_l);
  init_encoder(&odometry->encoder_r,htim_r);

  start_encoder(&odometry->encoder_l);
  start_encoder(&odometry->encoder_r);

  HAL_TIM_Base_Start_IT(htim_poll);
}
