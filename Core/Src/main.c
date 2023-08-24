/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "LCD1602.h"
#include "max_matrix_stm32.h"
#include <stdio.h>
#include <stdlib.h>

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
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
int press = 0;
int key = 0;
int op = 0;
int num1 = 0;
int num2 = 0;
int num3 = 0;

char string1[20];
char string2[20];
char string3[20];
char string4[20];
char string5[20];
char string6[20];
char string7[20];
char string8[20];

int add = 0;
int total = 0;
int dinero = 0;

int m1 = 0;
int m2 = 0;
int m3 = 0;
int m4 = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//ESTA PARTE CORRESPONDE A LAS FUNCIONES DEL STEPPER MOTOR

void stepper_stop() //ESTE VOID PERMITE QUE EL MOTOR SE DETENGA
	{
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);   //IN1
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);  //IN2
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);  //IN3
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);  //IN4
	  HAL_Delay(1);
	}


void stepper_pines_iz()//ESTE VOID SON LOS PINES DE MOVIMIENTO A LA IZQUIERDA DEL STEPPER MOTOR
	{
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);   //IN1
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);  //IN2
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);  //IN3
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);  //IN4
	  HAL_Delay(5);

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);   //IN1
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);  //IN2
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);  //IN3
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);  //IN4
	  HAL_Delay(5);

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);   //IN1
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);  //IN2
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);  //IN3
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);  //IN4
	  HAL_Delay(5);

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);   //IN1
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);  //IN2
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);  //IN3
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);  //IN4
	  HAL_Delay(5);
	}


void stepper_pines_der() //ESTE VOID SON LOS PINES DE MOVIMIENTO A LA DERECHA DEL STEPPER MOTOR
	{
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);   //IN1
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);  //IN2
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);  //IN3
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);  //IN4
	  HAL_Delay(5);

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);   //IN1
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);  //IN2
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);  //IN3
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);  //IN4
	  HAL_Delay(5);

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);   //IN1
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);  //IN2
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);  //IN3
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);  //IN4
	  HAL_Delay(5);

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);   //IN1
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);  //IN2
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);  //IN3
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);  //IN4
	  HAL_Delay(5);
	}


void pineskey()	//ESTE VOID SON LOS PINES DE SALIDA DEL KEYPAD
	{
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	  	  HAL_Delay(1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);


	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
	 	  HAL_Delay(1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);


	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
	  	  HAL_Delay(1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);


	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	  	  HAL_Delay(1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	}


void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin) //ESTA FUNCION SON LAS SALIDAS DEL KEYPAD
{

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
		{
		press++;
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
		{
			key = 1;
		}

		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
		{
			key = 4;
		}

		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
		{
			key = 7;
		}

		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))
		{
			key = 10;
		}
	}



	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1))
		{
		press++;
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
		{
			key = 2;
		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
		{
			key = 5;
		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
		{
			key = 8;
		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))
		{
			key = 0;
		}

	}



	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))
		{
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
		{
			key = 3;
		}

		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
		{
			key = 6;
		}

		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
		{
			key = 9;
		}

		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))
		{
			add = 1;
		}
	}


	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))
		{
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
		{
			op = 1;
		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
		{
			op = 2;
		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
		{
			op = 3;
		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))
		{
			op = 4;

		}

	}

}


void org() //ESTE VOID PERMITE QUE EL MOTOR SE POSICIONE Y MUESTRE ORGANIZANDO EN LA PANTALLA

	{
	stepper_pines_iz();
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Organizando...");
	write_char (24 ,1);
	}
		  //TAMBIEN ACTIVA EL LED ROJO Y EL BUZZER

void intro() //ESTE VOID MUESTRA EL MENSAJE INTRODUZCA LA MONEDA EN EL LCD
	{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		lcd_clear();
		lcd_put_cur(0, 0);
		lcd_send_string("Introduzca la");
		lcd_put_cur(1, 4);
		lcd_send_string("moneda");
			HAL_Delay(6000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	}



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
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_Base_Start(&htim2);


  max_init (0x03);
  lcd_init ();

  lcd_send_string ("Proyecto Final");
  write_char ('$' ,1);


  HAL_Delay(3000);

  max_clear();
  lcd_clear();

/* USER CODE END 2 */

/* Infinite loop */
/* USER CODE BEGIN WHILE */
while (1)
{


	  pineskey();
	  HAL_Delay(100);


	itoa(total,string3,10);
	itoa(dinero,string4,10);


	switch(op)
	{
	case 0:  //ESTA PARTE DEL SWITCH PERMITE SELECCIONAR LA OPCION EN EL LCD CON EL KEYPAD

		  max_clear();
		  lcd_clear();
		  lcd_put_cur(0, 0);
		  lcd_send_string("A. Introducir");
		  lcd_put_cur(1, 2);
		  lcd_send_string(" moneda");
		  HAL_Delay(1000);

		  lcd_clear();
		  lcd_put_cur(0, 0);
		  lcd_send_string("B. Ver cantidad ");
		  lcd_put_cur(1, 2);
		  lcd_send_string("  total");
		  HAL_Delay(1000);

		  lcd_clear();
		  lcd_put_cur(0, 0);
		  lcd_send_string("C. Dinero total ");
		  HAL_Delay(1000);

		  lcd_clear();
		  lcd_put_cur(0, 0);
		  lcd_send_string("D. Mantenimiento");
		  HAL_Delay(1000);
		  break;


	case 1:
		//ESTA PARTE PERMITE SABER CUANTAS MONEDAS HAY DE CADA TIPO Y PERMITE HACER GIRAR EL MOTOR

				//PARA QUE EL PROGRAMA SE POSICIONE EN EL REGLON DE 1 PESO
					if(num1 == 1 && add == 1 && num3 == 0)
						{
						m1++;
						total++;
						}

				//PARA QUE EL PROGRAMA SE POSICIONE EN EL REGLON DE 5 PESOS
					if(num1 == 5 && add ==1)
						{
						for(int ciclo=0; ciclo<110; ciclo++)
							{
							org();
							}

							intro();


						for(int ciclo=0; ciclo<110; ciclo++)
								  		{
										stepper_pines_der();
										write_char (25 ,1);
								  		}
						max_clear();
						m2++;
						total++;
						}




				//PARA QUE EL PROGRAMA SE POSICIONE EN EL REGLON DE 10 PESOS
				  if(num3 == 10 && add ==1)
						{
				  	for(int ciclo=0; ciclo<220; ciclo++)
				  		{
				  		org();
				  		}
				  	intro();


				  		for(int ciclo=0; ciclo<220; ciclo++)
				  				  		{
				  						stepper_pines_der();
				  						write_char (25 ,1);
				  				  		}

						m3++;
						total++;
						}

				//PARA QUE EL PROGRAMA SE POSICIONE EN EL REGLON DE 25 PESOS
				  if(num3 == 25 && add ==1)
						{
				  	for(int ciclo=0; ciclo<360; ciclo++)
							{
							org();
							}

							intro();


				  		for(int ciclo=0; ciclo<360; ciclo++)
				  				  		{
				  						stepper_pines_der();
				  						write_char (25 ,1);
				  				  		}
						m4++;
						total++;
						}

				  	break;


	case 2:  //ESTA PARTE MUESTRA LA CANTIDAD DE MONEDAS EN EL LCD

		if(add == 0)
			{
		  pineskey();
		  lcd_clear();
		  lcd_put_cur(0, 0);
		  lcd_send_string("monedas total:");
		  lcd_send_string(string3);
		  HAL_Delay(2000);

		  pineskey();
		  lcd_clear();
		  lcd_put_cur(0, 0);
		  lcd_send_string("monedas de 1: ");
		  lcd_send_string(string5);
		  HAL_Delay(2000);

		  pineskey();
		  lcd_clear();
		  lcd_put_cur(0, 0);
		  lcd_send_string("monedas de 5: ");
		  lcd_send_string(string6);
		  HAL_Delay(2000);

		  pineskey();
		  lcd_clear();
		  lcd_put_cur(0, 0);
		  lcd_send_string("monedas de 10: ");
		  lcd_send_string(string7);
		  HAL_Delay(2000);

		  pineskey();
		  lcd_clear();
		  lcd_put_cur(0, 0);
		  lcd_send_string("monedas de 25: ");
		  lcd_send_string(string8);
		  HAL_Delay(1000);
			}
		  break;

	case 3: //ESTA PARTE MUESTRA LA CANTIAD DE DINERO EN EL LCD

		if(add == 0)
			{
		  lcd_clear();
		  lcd_put_cur(0, 0);
		  lcd_send_string("Dinero total: ");
		  lcd_put_cur(1, 2);
		  lcd_send_string(string4);
		  lcd_send_string(" pesos");
		  HAL_Delay(1000);
			}
		  break;

	case 4: //ESTA PARTE HACE GIRAR EL STEPPER MOTOR Y ENCIENDE EL VENTILADOR

		if(add == 0)
			{


			  htim1.Instance->CCR2 = 50;  // duty cycle is 1.5 ms
			  HAL_Delay(1000);
			  htim1.Instance->CCR2 = 125;  // duty cycle is .5 ms
			  HAL_Delay(1000);
			  htim1.Instance->CCR2 = 175;  // duty cycle is 2.5 ms
			  HAL_Delay(1000);
			  htim1.Instance->CCR2 = 100;  // duty cycle is .5 ms
			  HAL_Delay(1000);



		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
		lcd_clear();
		lcd_put_cur(0, 0);
		lcd_send_string("Mantenimiento...");
		HAL_Delay(1000);
			}
	}




	  itoa(num1,string1,10);
	  itoa(num3,string2,10);

//ESTA PARTE MUESTRA EN LA PANTALLA EL MENSAJE  INGRESE EL VALOR
	  if(op == 1 && press == 0)
	 	  {
	 			  lcd_clear();
	 			  lcd_put_cur(0, 0);
	 			  lcd_send_string("Ingrese el valor:");
	 			  HAL_Delay(1000);
	 	  }


	  if(op == 1 && press == 1)
	 	  {
		  	  	  //ESTA PARTE PERMITE INTRODUCIR LOS NUMEROS CON EL KEYPAD
		  	  	  num1 = key;

	 			  lcd_clear();
	 			  lcd_put_cur(0, 0);
	 			  lcd_send_string("Ingrese el valor:");
	 			  lcd_put_cur(1, 4);
	 			  lcd_send_string(string1);
	 			  lcd_send_string(" pesos");
	 			  HAL_Delay(1000);
	 	  }



	  if(op == 1 && press >=2)
	 	 	  {

		  	  	  //ESTA PARTE PERMITE INTRODUCIR LOS NUMEROS CON EL KEYPAD
		  	  	  	  num2 = key;
		  			  num3 = num1 * 10 + num2 ;

		  	  	  	  lcd_clear();
	 	 			  lcd_put_cur(0, 0);
	 	 			  lcd_send_string("Ingrese el valor:");
	 	 			  lcd_put_cur(1, 4);
	 	 			  lcd_send_string(string2);
	 	 			  lcd_send_string(" pesos");
	 	 			  HAL_Delay(1000);
	 	 	  }








//ESTA PARTE PERMITE OBTENER LA SUMA TOTAL DEL DINERO
	if(num1 <= 5 && num3 == 0 && add == 1)
		{
		dinero = dinero + num1;
		}

	if(num3 > 0 && add == 1)
		{
		dinero = dinero + num3;
		}




	itoa(m1,string5,10);
	itoa(m2,string6,10);
	itoa(m3,string7,10);
	itoa(m4,string8,10);



//ESTA PARTE PERMITE REGRESAR EL PROGRAMA AL MENU PRINCIPAL
	if(add == 1)
		{
		key = 0;
		press = 0;
		op = 0;
		num1 = 0;
		num2 = 0;
		num3 = 0;
		add = 0;
		}


	  	  }
/* USER CODE END 3 */
		}

/* USER CODE END WHILE */
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 1800;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1000-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 180-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, data_Pin|cs_Pin|clock_Pin|GPIO_PIN_12
                          |GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC4 PC5
                           PC6 PC7 PC8 PC9
                           PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA4 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : data_Pin cs_Pin clock_Pin PA12
                           PA15 */
  GPIO_InitStruct.Pin = data_Pin|cs_Pin|clock_Pin|GPIO_PIN_12
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB10 PB12
                           PB13 PB14 PB15 PB4
                           PB5 PB6 PB7 PB8
                           PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
