/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "encoder.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_USART2_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim3);
  HAL_TIM_Base_Start(&htim5);
  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim5);
	HAL_TIM_PWM_Start(& htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(& htim3, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(& htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(& htim3, TIM_CHANNEL_4);
  //distance_encoder=10;

/*
void navigation(asservissement* asserv,parametre* cstes){
    int i=0;
    (asserv->perreur)->x=255;
    (asserv->perreur)->y=255;
    
    *(asserv->pconsigne->gauche)=255;
    *(asserv->pconsigne->droite)=255;
    commande_moteur((asserv->pconsigne->gauche),(asserv->pconsigne->droite));
}
*/
  //void init(int nbpoint,int epsilon,Point* cap,int* ptheta,unsigned int* cnt_droite,
//  unsigned int* cnt_gauche,unsigned int* pdistanceparcourue_droite,unsigned int* pdistanceparcourue_gauche,int* px,int* py,int* moy_prev,int* pconsigne_gauche,int* pconsigne_droite);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
       // htim3.Instance->CCR1 = 160;
      //htim3.Instance->CCR2 = 0;
      //htim3.Instance->CCR3 = 130;
      //htim3.Instance->CCR4 = 0;
     /**pconsigne_droite=120;
     *pconsigne_gauche=120;
     commande_moteur(pconsigne_gauche,pconsigne_droite);*///commande des moteurs fonctionne
    *px=0;
    *py=0;
    consigne(0.1,200,0,px,py,pconsigne_gauche,pconsigne_droite,0);
    commande_moteur(pconsigne_gauche,pconsigne_droite);
    printf(" %ld \n",(&htim2)->Instance->CNT);
    printf(" %ld \n",(&htim5)->Instance->CNT);
    theta(ptheta,cnt_droite,cnt_gauche,distance_encoder);
    mise_a_jour_distance(pdistanceparcourue_droite,pdistanceparcourue_gauche);
    mise_a_jour_x_y(px,py,ptheta,moy_prev,pdistanceparcourue_droite,pdistanceparcourue_gauche);
    /*
   
    */
    ///*
    //commande_moteur((asserv->pconsigne->gauche),(asserv->pconsigne->droite));
    //*/
    //navigation(nbpoint,epsilon,cap,ptheta,cnt_droite, cnt_gauche, pdistanceparcourue_droite,pdistanceparcourue_gauche, px, py, moy_prev, pconsigne_gauche,pconsigne_droite);

    //    navigation(asserv,cstes);
  
   
/*
  int i=0;
  int erreur_x=255;
  int erreur_y=255;
  int objectif_x=20;
  int objectif_y=20;
/*  for(i=0;i<nbpoint;i++){
    objectif_x=(cap+i)->x;
    objectif_y=(cap+i)->y;
*/
  //  while(epsilon<erreur_x || epsilon<erreur_y){
//*//*
/*
      theta(ptheta,cnt_droite,cnt_gauche,distance_encoder);
      mise_a_jour_distance(pdistanceparcourue_droite,pdistanceparcourue_gauche);
      mise_a_jour_x_y(px,py,ptheta,moy_prev,pdistanceparcourue_droite,pdistanceparcourue_gauche);

      consigne(epsilon,objectif_x,objectif_y,px,py,pconsigne_gauche,pconsigne_droite,ptheta);
    
      //*pconsigne_gauche=120;
      //*pconsigne_droite=120;
     /* if (*px>0.001){*/
/*      commande_moteur(pconsigne_gauche,pconsigne_droite);
      erreur_x=*px-objectif_x;
      erreur_y=*py-objectif_y;
    /*}
    else{
      htim3.Instance->CCR1 = 0;
      htim3.Instance->CCR2 = 0;
      htim3.Instance->CCR3 = 0;
      htim3.Instance->CCR4 = 0;
    }}*/
    }
  }


  
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
  
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
