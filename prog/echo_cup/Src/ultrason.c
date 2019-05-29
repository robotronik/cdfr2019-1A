int detectionUS(){
	//envoie signal trigger
    HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_7);
    HAL_Delay(0.1);
    HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_7);


    count = __HAL_TIM_GetCounter(&htim1); //unite cm
    //input_capture = __HAL_TIM_GetCompare(&htim1,TIM_CHANNEL_1);
    HAL_Delay(100);
	
	return count;
}