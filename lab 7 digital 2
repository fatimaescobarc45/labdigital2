/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
volatile uint8_t contador = 0;
volatile uint8_t contadorRGB = 0;
volatile uint8_t modo = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void actualizarLeds(uint8_t valor);
void actualizarRGB(uint8_t valor);
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // --- Lógica para el botón de MODO ---
	      // 1. Detectamos si el botón está presionado (LOW, porque es pull-up)
	      if (HAL_GPIO_ReadPin(bmodo_GPIO_Port, bmodo_Pin) == GPIO_PIN_RESET) {
	          // 2. Hacemos la pausa para el antirrebote
	          HAL_Delay(50);
	          // 3. Confirmamos que sigue presionado
	          if (HAL_GPIO_ReadPin(bmodo_GPIO_Port, bmodo_Pin) == GPIO_PIN_RESET) {
	              modo = !modo; // Invertimos el modo UNA SOLA VEZ
	              HAL_GPIO_WritePin(ledModo_GPIO_Port, ledModo_Pin, modo);

	              // 4. Esperamos a que se suelte el botón para no registrar más pulsaciones
	              while(HAL_GPIO_ReadPin(bmodo_GPIO_Port, bmodo_Pin) == GPIO_PIN_RESET);
	          }
	      }

	      // --- Lógica para el botón de SUMA ---
	      if (HAL_GPIO_ReadPin(bsuma_GPIO_Port, bsuma_Pin) == GPIO_PIN_RESET) {
	          HAL_Delay(50);
	          if (HAL_GPIO_ReadPin(bsuma_GPIO_Port, bsuma_Pin) == GPIO_PIN_RESET) {
	              if (modo == 0) { // Modo Contador Binario
	                  contador++;
	                  if (contador > 4) contador = 0;
	                  actualizarLeds(contador);
	              } else { // Modo LED RGB
	                  contadorRGB++;
	                  if (contadorRGB > 6) contadorRGB = 0;
	                  actualizarRGB(contadorRGB);
	              }
	              // Esperamos a que se suelte el botón
	              while(HAL_GPIO_ReadPin(bsuma_GPIO_Port, bsuma_Pin) == GPIO_PIN_RESET);
	          }
	      }

	      // --- Lógica para el botón de RESTA ---
	      if (HAL_GPIO_ReadPin(bresta_GPIO_Port, bresta_Pin) == GPIO_PIN_RESET) {
	          HAL_Delay(50);
	          if (HAL_GPIO_ReadPin(bresta_GPIO_Port, bresta_Pin) == GPIO_PIN_RESET) {
	              if (modo == 0) { // Modo Contador Binario
	                  if (contador == 0) contador = 4;
	                  else contador--;
	                  actualizarLeds(contador);
	              } else { // Modo LED RGB
	                  if (contadorRGB == 0) contadorRGB = 6;
	                  else contadorRGB--;
	                  actualizarRGB(contadorRGB);
	              }
	              // Esperamos a que se suelte el botón
	              while(HAL_GPIO_ReadPin(bresta_GPIO_Port, bresta_Pin) == GPIO_PIN_RESET);
	          }
	      }
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  /*
	  int botonSuma = !HAL_GPIO_ReadPin(GPIOA, bsuma_Pin);
	  int botonResta = !HAL_GPIO_ReadPin(GPIOB, bresta_Pin);
	  int botonModo = !HAL_GPIO_ReadPin(GPIOB, bmodo_Pin);

	  if(botonModo){
		  while(botonModo){
			  modo=(!modo);
			  botonModo = HAL_GPIO_ReadPin(GPIOB, bmodo_Pin);
		  }
	  }

	  if(botonSuma){
	    while(botonSuma){
	      if(!modo){
	        contador++;
	      } else {
	        contadorRGB++;
	      }
	      botonSuma = HAL_GPIO_ReadPin(GPIOA, bsuma_Pin);
	    }
	    if(contador>4) contador=4;
	    if(contadorRGB>6) contadorRGB=6;
	  }
	  if(botonResta){
	  		  while(botonResta){
	  			  if(!modo){
	  				  contador--;
	  			  }
	  			  else{
	  				  contadorRGB--;
	  			  }
	  			  botonResta=HAL_GPIO_ReadPin(GPIOA, bresta_Pin);
	  		  }

	  	  }
	  actualizarLeds(contador);
	  actualizarRGB(contadorRGB);
	  HAL_GPIO_WritePin(ledModo_GPIO_Port, ledModo_Pin, modo);


	  }
	  */


  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
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

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|cont3_Pin|cont2_Pin|ledG_Pin
                          |ledB_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ledR_Pin|cont1_Pin|ledModo_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(cont0_GPIO_Port, cont0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin cont3_Pin cont2_Pin ledG_Pin
                           ledB_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|cont3_Pin|cont2_Pin|ledG_Pin
                          |ledB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ledR_Pin cont1_Pin ledModo_Pin */
  GPIO_InitStruct.Pin = ledR_Pin|cont1_Pin|ledModo_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : cont0_Pin */
  GPIO_InitStruct.Pin = cont0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(cont0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : bmodo_Pin */
  GPIO_InitStruct.Pin = bmodo_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(bmodo_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : bsuma_Pin bresta_Pin */
  GPIO_InitStruct.Pin = bsuma_Pin|bresta_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void actualizarLeds(uint8_t valor) {
    // Usamos operaciones bitwise para encender o apagar cada LED.
	switch(valor){
		case 0:
			HAL_GPIO_WritePin(cont0_GPIO_Port, cont0_Pin, 0);
			HAL_GPIO_WritePin(cont1_GPIO_Port, cont1_Pin, 0);
			HAL_GPIO_WritePin(cont2_GPIO_Port, cont2_Pin, 0);
			HAL_GPIO_WritePin(cont3_GPIO_Port, cont3_Pin, 0);
			break;
		case 1:
			HAL_GPIO_WritePin(cont0_GPIO_Port, cont0_Pin, 1);
			HAL_GPIO_WritePin(cont1_GPIO_Port, cont1_Pin, 0);
			HAL_GPIO_WritePin(cont2_GPIO_Port, cont2_Pin, 0);
			HAL_GPIO_WritePin(cont3_GPIO_Port, cont3_Pin, 0);
			break;
		case 2:
			HAL_GPIO_WritePin(cont0_GPIO_Port, cont0_Pin, 1);
			HAL_GPIO_WritePin(cont1_GPIO_Port, cont1_Pin, 1);
			HAL_GPIO_WritePin(cont2_GPIO_Port, cont2_Pin, 0);
			HAL_GPIO_WritePin(cont3_GPIO_Port, cont3_Pin, 0);
			break;
		case 3:
			HAL_GPIO_WritePin(cont0_GPIO_Port, cont0_Pin, 1);
			HAL_GPIO_WritePin(cont1_GPIO_Port, cont1_Pin, 1);
			HAL_GPIO_WritePin(cont2_GPIO_Port, cont2_Pin, 1);
			HAL_GPIO_WritePin(cont3_GPIO_Port, cont3_Pin, 0);
			break;
		case 4:
			HAL_GPIO_WritePin(cont0_GPIO_Port, cont0_Pin, 1);
			HAL_GPIO_WritePin(cont1_GPIO_Port, cont1_Pin, 1);
			HAL_GPIO_WritePin(cont2_GPIO_Port, cont2_Pin, 1);
			HAL_GPIO_WritePin(cont3_GPIO_Port, cont3_Pin, 1);
			break;

	}



}
void actualizarRGB(uint8_t valor) {
    // Usamos operaciones bitwise para encender o apagar cada LED.
	switch(valor){
	case 0:
		HAL_GPIO_WritePin(ledR_GPIO_Port, ledR_Pin, 0);
		HAL_GPIO_WritePin(ledG_GPIO_Port, ledG_Pin, 0);
		HAL_GPIO_WritePin(ledB_GPIO_Port, ledB_Pin, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(ledR_GPIO_Port, ledR_Pin, 1);
		HAL_GPIO_WritePin(ledG_GPIO_Port, ledG_Pin, 0);
		HAL_GPIO_WritePin(ledB_GPIO_Port, ledB_Pin, 0);
		break;
	case 2:
		HAL_GPIO_WritePin(ledR_GPIO_Port, ledR_Pin, 1);
		HAL_GPIO_WritePin(ledG_GPIO_Port, ledG_Pin, 0);
		HAL_GPIO_WritePin(ledB_GPIO_Port, ledB_Pin, 1);
		break;
	case 3:
		HAL_GPIO_WritePin(ledR_GPIO_Port, ledR_Pin, 0);
		HAL_GPIO_WritePin(ledG_GPIO_Port, ledG_Pin, 0);
		HAL_GPIO_WritePin(ledB_GPIO_Port, ledB_Pin, 1);
		break;
	case 4:
		HAL_GPIO_WritePin(ledR_GPIO_Port, ledR_Pin, 0);
		HAL_GPIO_WritePin(ledG_GPIO_Port, ledG_Pin, 1);
		HAL_GPIO_WritePin(ledB_GPIO_Port, ledB_Pin, 1);
		break;
	case 5:
		HAL_GPIO_WritePin(ledR_GPIO_Port, ledR_Pin, 0);
		HAL_GPIO_WritePin(ledG_GPIO_Port, ledG_Pin, 1);
		HAL_GPIO_WritePin(ledB_GPIO_Port, ledB_Pin, 0);
		break;
	case 6:
		HAL_GPIO_WritePin(ledR_GPIO_Port, ledR_Pin, 1);
		HAL_GPIO_WritePin(ledG_GPIO_Port, ledG_Pin, 1);
		HAL_GPIO_WritePin(ledB_GPIO_Port, ledB_Pin, 0);
		break;


	}



}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
