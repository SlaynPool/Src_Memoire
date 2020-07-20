#include "main.h"

#include "stm32f4xx_hal.h"





TIM_HandleTypeDef htim3;



void SystemClock_Config(void);

void Error_Handler(void);

static void MX_GPIO_Init(void);

static void MX_TIM3_Init(void);                                    

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

                               



int main(void)

{



  HAL_Init();



  SystemClock_Config();



  MX_GPIO_Init();

  MX_TIM3_Init();



	uint8_t increment = 0;  // define a variable to increase the duty cycle

	

	HAL_TIM_PWM_Start (&htim3, TIM_CHANNEL_1);



  while (1)

  {



		if (!(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_13)))   // if the user button is pressed

		{

			while (!(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_13)));  // wait for the button to be released

			

			htim3.Instance->CCR1 = increment;   // increase the pulse width in the steps of 10

			increment+=10;  // increment in 10 steps or by 10% for the duty cycle

			if (increment>100) increment =0;   // if increment is > 100 than reset its value to 0

		}

	}





}



/** System Clock Configuration

*/

void SystemClock_Config(void)

{



  RCC_OscInitTypeDef RCC_OscInitStruct;

  RCC_ClkInitTypeDef RCC_ClkInitStruct;



    /**Configure the main internal regulator output voltage 

    */

  __HAL_RCC_PWR_CLK_ENABLE();



  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);



    /**Initializes the CPU, AHB and APB busses clocks 

    */

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;

  RCC_OscInitStruct.HSIState = RCC_HSI_ON;

  RCC_OscInitStruct.HSICalibrationValue = 16;

  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;

  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;

  RCC_OscInitStruct.PLL.PLLM = 16;

  RCC_OscInitStruct.PLL.PLLN = 336;

  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;

  RCC_OscInitStruct.PLL.PLLQ = 7;

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



    /**Configure the Systick interrupt time 

    */

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);



    /**Configure the Systick 

    */

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);



  /* SysTick_IRQn interrupt configuration */

  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

}



/* TIM3 init function */

static void MX_TIM3_Init(void)

{



  TIM_ClockConfigTypeDef sClockSourceConfig;

  TIM_MasterConfigTypeDef sMasterConfig;

  TIM_OC_InitTypeDef sConfigOC;



  htim3.Instance = TIM3;

  htim3.Init.Prescaler = 84-1;

  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;

  htim3.Init.Period = 100-1;

  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)

  {

    Error_Handler();

  }



  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)

  {

    Error_Handler();

  }



  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)

  {

    Error_Handler();

  }



  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;

  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)

  {

    Error_Handler();

  }



  sConfigOC.OCMode = TIM_OCMODE_PWM1;

  sConfigOC.Pulse = 0;

  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;

  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)

  {

    Error_Handler();

  }



  HAL_TIM_MspPostInit(&htim3);



}



static void MX_GPIO_Init(void)

{



  GPIO_InitTypeDef GPIO_InitStruct;



  /* GPIO Ports Clock Enable */

  __HAL_RCC_GPIOC_CLK_ENABLE();

  __HAL_RCC_GPIOA_CLK_ENABLE();



  /*Configure GPIO pin : PC13 */

  GPIO_InitStruct.Pin = GPIO_PIN_13;

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

  GPIO_InitStruct.Pull = GPIO_PULLUP;

  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);



}



void Error_Handler(void)

{



  while(1) 

  {

  }



}



#ifdef USE_FULL_ASSERT



void assert_failed(uint8_t* file, uint32_t line)

{



}



#endif


