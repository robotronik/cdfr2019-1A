#include "motor.h"

void setPWM(TIM_HandleTypeDef * timer, uint32_t channel, uint16_t period, uint16_t pulse) {   
        HAL_TIM_PWM_Stop(timer, channel);    // stop generation of pwm  

        TIM_OC_InitTypeDef sConfigOC;   
        timer->Init.Period = period;           // set the period duration  
        HAL_TIM_PWM_Init(timer);  // reinititialise with new period value  

        sConfigOC.OCMode = TIM_OCMODE_PWM1;   
        sConfigOC.Pulse = pulse;              // set the pulse duration   
        sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;   
        sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;   

        HAL_TIM_PWM_ConfigChannel(timer, &sConfigOC, channel);   
        HAL_TIM_PWM_Start(timer, channel);   // start pwm generation
    } 
    //also possible : htim.Instance->CCR1 =120;

//other
void motorSetValue(TIM_HandleTypeDef * timer, uint32_t channel, uint16_t pulse){
    switch(channel){
        case 1:
            timer->Instance->CCR1 = pulse;
        break;
        case 2:
            timer->Instance->CCR2 = pulse;
        break;
        case 3:
            timer->Instance->CCR3 = pulse;
        break;
        case 4:
            timer->Instance->CCR4 = pulse;
        break;
    }
}

//see for macro in .h for simpler motor control ,
// you have to modify some of the #define in order to adapt the code to your needs
void motorControl(TIM_HandleTypeDef * timer,int value,uint8_t ismLeft){
    // a verifier
    if(value > 254) value =254;
    else if(value <-254) value= -254;
    
    if (ismLeft==1){
        if(value > 0){
            motorSetValue(timer, 1,value);
            motorSetValue(timer, 2,0);
        }
        else{
            motorSetValue(timer, 1,0);
            motorSetValue(timer, 2,-value);
        }
    }
    else{
        if(value>0){
            motorSetValue(timer, 3,value);
            motorSetValue(timer, 4,0);            
        }
        else{
            motorSetValue(timer, 3,0);
            motorSetValue(timer, 4,-value);
        }
    }
}