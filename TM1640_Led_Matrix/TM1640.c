/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// подключение:
//	пин PB6 CLK 	режим просто OUTPUT
//	пин PB7 DIN		режим просто OUTPUT
//////////////////////////////////////////////////////////////////////

#include "TM1640.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
static void MX_GPIO_Init(void);
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
  /* USER CODE BEGIN 2 */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	uint8_t flag = 0;							// флаг чтоб поочереди было сперва бегущая строка после анимация и покругу
	
	extern int32_t x;
	extern int32_t y;
	extern uint8_t *frameBuffer;
	
	extern uint8_t a[8];
	extern uint8_t b[8];
	
	frameBuffer = (uint8_t *)malloc( 16 );  			// создаем массив буффер для нашего экрана размер равен кол-ву столбцов ( унвс их 16 )
  
	TM1640_brightness(1);								// устанавливаем подсветка значение от 0 до 7
	TM1640_clearDisplay();
	// TM1640_display_byte(15,0xF0);					// прорисовываем ( если нужно ) в последней строке 1 байт ( 0xF0 = получаем 11110000 )


	// Создаем строку для отображения функция utf8rus() выделит динамическую память под
	// нужный размер и вернет на нее указатель
	// в начале и в конце не забываем ставить пробелы для красивого отображения текста
	char *myText = utf8rus( " Привет Мир 12345 Hello Jon QWERTY " );
	// незабываем каждый раз после вызова функции utf8rus() освобождать память
	free( pText );	// освобождаем память выделенную в функции utf8rus() посредством malloc();
				
	// ТОЛЬКО для отображения анимации------------------------------------------------------
	// x = ( 8*MATRIXS_QUANTITY );	// ставим для движения анимации с права на лево
	// x = 0; // для движения анимации с лево на право
	//---------------------------------------------------------------------------------------
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	  
	
		// вывод бегущей строки
		if( !flag){
					  
			int len = strlen( myText );						// Узнаем длину нашего текста
			
			TM1640_drawString_buff( myText, len, x, 0 );	// выводим на экран наш текст				  
			TM1640_display_Draw();							// отображаем на дисплее то что нарисовали выше
			
			HAL_Delay(100);									// задержка ( регулирует скорость прокрутки )

			if( --x < len * -8 ) {
				x = (16);
				flag=1;
			}
		}					  
					
//*************************************************************************	
		// вывод анимации
		else{					
					
			clear_buff();
			drawSprite( (uint8_t*)&a, x--, 0, 8, 8 ); 	// Х-- ставим для движения анимации с права на лево, Х++ для движения анимации с лево на право
			TM1640_display_Draw();						// отображаем на дисплее то что нарисовали выше
			
			HAL_Delay(200);

			clear_buff();
			drawSprite( (uint8_t*)&b, x--, 0, 8, 8 );	// Х-- ставим для движения анимации с права на лево, Х++ для движения анимации с лево на право
			TM1640_display_Draw();						// отображаем на дисплее то что нарисовали выше
			
			HAL_Delay(200);
					
			// внимание выводим столько кадров сколько есть в массиве ( в данном случае два кадра )
				
			//-- для движения анимации с лево на право -----------
			//	if( x > ( 16 ) ){
			//		x= -1;
			//	}
			//-----------------------------------------------------------

			//-----------------------------------------------------------	  
			//-- для движения анимации с права на лево -------------
				if( x <-6){
					x= ( 16 );
					flag=0;
				}
			//---------------------------------------------				
		}	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
