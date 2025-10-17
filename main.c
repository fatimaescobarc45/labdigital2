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
volatile uint8_t posicionA = 0;
volatile uint8_t posicionB = 0;
volatile uint8_t juegoActivo = 0;   // 1 = los jugadores pueden avanzar
volatile uint8_t juegoListo = 0;    // 1 = se recibió 'S' y hay que ejecutar semáforo
uint8_t ganador = 0;                 // 0 = nadie, 1 = jugador A, 2 = jugador B
uint8_t rxData;                       // dato UART recibido
#define MAX_POS 4
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  HAL_UART_Receive_IT(&huart2, &rxData, 1); // <-- habilita interrupción UART

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // --- Secuencia de semáforo ---
	     if (juegoListo && !juegoActivo)
	     {
	         // Bloquea botones automáticamente con juegoActivo = 0

	         // LED Rojo (1 s)
	         HAL_GPIO_WritePin(ledR_GPIO_Port, ledR_Pin, GPIO_PIN_SET);
	         HAL_Delay(1000);
	         HAL_GPIO_WritePin(ledR_GPIO_Port, ledR_Pin, GPIO_PIN_RESET);

	         // LED Amarillo (1 s)
	         HAL_GPIO_WritePin(ledY_GPIO_Port, ledY_Pin, GPIO_PIN_SET);
	         HAL_Delay(1000);
	         HAL_GPIO_WritePin(ledY_GPIO_Port, ledY_Pin, GPIO_PIN_RESET);

	         // LED Verde (1 s)
	         HAL_GPIO_WritePin(ledG_GPIO_Port, ledG_Pin, GPIO_PIN_SET);
	         HAL_Delay(1000);
	         HAL_GPIO_WritePin(ledG_GPIO_Port, ledG_Pin, GPIO_PIN_RESET);

	         // Semáforo terminado, los jugadores pueden jugar
	         juegoActivo = 1;
	         juegoListo = 0;
	     }

	     // --- Juego activo ---
	     if (juegoActivo)
	     {
	         actualizarLeds();  // función que enciende LEDs según posiciónA/B

	         // Verificar ganador
	         if (posicionA >= MAX_POS)
	         {
	             ganador = 1;
	             juegoActivo = 0;  // bloquea botones
	             // Notificación por UART
	             char msg[] = "Jugador A gano!\r\n";
	             HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	         }
	         else if (posicionB >= MAX_POS)
	         {
	             ganador = 2;
	             juegoActivo = 0;
	             // Notificación por UART
	             char msg[] = "Jugador B gano!\r\n";
	             HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	         }
	     }

	     // --- Finalizado ---
	     if (!juegoActivo && ganador != 0)
	     {
	         // Aquí puedes decidir: mantener LEDs del ganador encendidos, parpadeo, etc.
	         // El juego NO se reinicia hasta recibir otro 'S' por UART
	     }
  }

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
  HAL_GPIO_WritePin(GPIOC, ledG_Pin|ledY_Pin|led3B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|led1B_Pin|led4A_Pin|led4B_Pin
                          |led1A_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ledR_Pin|led3A_Pin|led2A_Pin|led2B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ledG_Pin ledY_Pin led3B_Pin */
  GPIO_InitStruct.Pin = ledG_Pin|ledY_Pin|led3B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin led1B_Pin led4A_Pin led4B_Pin
                           led1A_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|led1B_Pin|led4A_Pin|led4B_Pin
                          |led1A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ledR_Pin led3A_Pin led2A_Pin led2B_Pin */
  GPIO_InitStruct.Pin = ledR_Pin|led3A_Pin|led2A_Pin|led2B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : botonA_Pin botonB_Pin */
  GPIO_InitStruct.Pin = botonA_Pin|botonB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static uint32_t lastTickA = 0;
    static uint32_t lastTickB = 0;
    uint32_t now = HAL_GetTick();

    if (GPIO_Pin == botonA_Pin)
    {
        if ((now - lastTickA) > 50)    // 50 ms debounce
        {
        	if (juegoActivo && (posicionA < MAX_POS)) posicionA++;

            lastTickA = now;
        }
    }
    else if (GPIO_Pin == botonB_Pin)
    {
        if ((now - lastTickB) > 50)    // 50 ms debounce
        {
            if (juegoActivo &&(posicionB < MAX_POS)) posicionB++;
            lastTickB = now;
        }
    }
}

void actualizarLeds(void)
{
    /* --- Jugador A --- */
    if (posicionA > 0) HAL_GPIO_WritePin(led1A_GPIO_Port, led1A_Pin, GPIO_PIN_SET);
    else HAL_GPIO_WritePin(led1A_GPIO_Port, led1A_Pin, GPIO_PIN_RESET);

    if (posicionA > 1) HAL_GPIO_WritePin(led2A_GPIO_Port, led2A_Pin, GPIO_PIN_SET);
    else HAL_GPIO_WritePin(led2A_GPIO_Port, led2A_Pin, GPIO_PIN_RESET);

    if (posicionA > 2) HAL_GPIO_WritePin(led3A_GPIO_Port, led3A_Pin, GPIO_PIN_SET);
    else HAL_GPIO_WritePin(led3A_GPIO_Port, led3A_Pin, GPIO_PIN_RESET);

    if (posicionA > 3) HAL_GPIO_WritePin(led4A_GPIO_Port, led4A_Pin, GPIO_PIN_SET);
    else HAL_GPIO_WritePin(led4A_GPIO_Port, led4A_Pin, GPIO_PIN_RESET);

    /* --- Jugador B --- */
    if (posicionB > 0) HAL_GPIO_WritePin(led1B_GPIO_Port, led1B_Pin, GPIO_PIN_SET);
    else HAL_GPIO_WritePin(led1B_GPIO_Port, led1B_Pin, GPIO_PIN_RESET);

    if (posicionB > 1) HAL_GPIO_WritePin(led2B_GPIO_Port, led2B_Pin, GPIO_PIN_SET);
    else HAL_GPIO_WritePin(led2B_GPIO_Port, led2B_Pin, GPIO_PIN_RESET);

    if (posicionB > 2) HAL_GPIO_WritePin(led3B_GPIO_Port, led3B_Pin, GPIO_PIN_SET);
    else HAL_GPIO_WritePin(led3B_GPIO_Port, led3B_Pin, GPIO_PIN_RESET);

    if (posicionB > 3) HAL_GPIO_WritePin(led4B_GPIO_Port, led4B_Pin, GPIO_PIN_SET);
    else HAL_GPIO_WritePin(led4B_GPIO_Port, led4B_Pin, GPIO_PIN_RESET);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2) // verifica que sea el UART correcto
    {
        if (rxData == 'S' || rxData == 's') // si recibió 'S'
        {
      	  posicionA = 0;
      	  posicionB = 0;
      	  ganador = 0;
      	  actualizarLeds();
        	juegoListo = 1; // activa la secuencia del semáforo
        }

        // volver a habilitar la recepción por interrupción
        HAL_UART_Receive_IT(&huart2, &rxData, 1);
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
