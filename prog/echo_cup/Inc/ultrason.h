//AJOUTER DANS LE MAIN
/*
//USER CODE BEGIN 0
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
 if (htim->Instance==TIM1)
  {
    input_capture= __HAL_TIM_GetCounter(htim);    //read TIM2 channel 1 capture value
    __HAL_TIM_SetCounter(htim, 0);    //reset counter after input capture interrupt occurs
  }
}

//USER CODE BEGIN 2
HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_1);


*/

#include "gpio.h"
#include "tim.h"

int detectionUS();