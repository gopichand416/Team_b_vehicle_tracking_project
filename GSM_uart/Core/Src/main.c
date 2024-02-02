/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include<stdio.h>
#include<string.h>
#include"GSM.h"
int _write(int file,char *ptr,int len)
{
    int i=0;
    for(i=0;i<len;i++)
      ITM_SendChar((*ptr++));
    return len;
}
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
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_UART4_Init(void);
static void MX_UART5_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
uint8_t tx[]="AT\r\n";
uint8_t rx[200];
//uint8_t tx[]="AT\r\n";
//uint8_t rx[20];
uint8_t command[20];
uint8_t response[20];
char *data1;
uint8_t var=0;
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

}
char *send_to_gsm(char * command)
{
	memset(rx,'\0',sizeof(rx));
	 printf("tx start\n");
	 HAL_UART_Transmit_IT(&huart4, (uint8_t *)command,strlen(command));
	 HAL_UART_Receive(&huart4, rx, 200,1000);
	 printf("rx data %s\n",(char *)rx);
	 return (char *)rx;
}

int send_mesg_to_server(char *mes,int size)
{
	/*memset(rx,'\0',sizeof(rx));
	//char buf[50];
	//snprintf(buf,strlen("AT+CIPSEND=0,50\r"),"AT+CIPSEND=0,%d\r\n",strlen(mes));
	//printf("buf = %s\n",buf);
	//if(check_server_connection()==0)
	{
//		HAL_UART_Transmit_IT(&huart4, (uint8_t *)"AT+CIPSEND=0,9\r\n", strlen("AT+CIPSEND=0,9\r\n"));
		//HAL_UART_Transmit_IT(&huart4, (uint8_t *)buf, strlen(buf));/
		HAL_UART_Transmit(&huart4, (uint8_t *)"AT+CIPSEND=0,9\r\n", strlen("AT+CIPSEND=0,911222\r\n"),1000);
		memset(rx,'\0',sizeof(rx)); // aiyaz
		HAL_Delay(2000);
		HAL_UART_Transmit_IT(&huart4,(uint8_t *) "hi vishnu",9);
		HAL_UART_Receive(&huart4, (uint8_t *)rx, 200,1000);*/
	{
		//char buf[]="{\"latitude\":1727.401123 N, \"longitude\":7822.510254 E, \"time\":12:48:30}";
		memset(rx,'\0',sizeof(rx));
		HAL_UART_Transmit_IT(&huart4,(uint8_t*)"AT+CIPSEND=0,7\r",16);
		HAL_UART_Receive(&huart4, rx, 200,3000);
		printf("Received data %s\n",rx);
		memset(rx,'\0',sizeof(rx));
		//HAL_UART_Transmit_IT(&huart4,(uint8_t*)"{\"latitude\":1727.401123 N, \"longitude\":7822.510254 E, \"time\":12:48:30}", strlen("{\"latitude\":1727.401123 N, \"longitude\":7822.510254 E, \"time\":12:48:30}"));
		HAL_UART_Transmit_IT(&huart4,(uint8_t*)"hiteam", 7);

		HAL_UART_Receive(&huart4, rx, 200,3000);
		printf("Received data %s\n",rx);

		if(strstr((char *)rx,"\r\nOK\r\n")!=NULL)
		{
			printf("mesg send successfully\n");
			return HAL_OK;
		}
		else
		{
			printf("mesg NOT send\n");
			return 1;
		}
	}
	return 1;
}
/*
int check(char *command, char *response)
{
	 if((check_signal(response))==0)
	 {
		 printf("match found\n");
		 return 1;
	 }
	 else
	 {
		 printf("match not found\n");
		 return 0;
	 }
	 printf("response data is %s\n",response);
  }
void send_at(char *command,char *response)
{
	memset(rx,'\0',sizeof(rx));
	 printf("tx start\n");
	 //HAL_UART_Transmit(&huart4, (uint8_t *)command,strlen(command),10);
	 HAL_UART_Transmit_IT(&huart4, (uint8_t *)command,strlen(command));
	 HAL_UART_Receive(&huart4, rx, 20,1000);
	 printf("rx data %s\n",(char *)rx);
	 var=check(rx,response);

	// return (char *)rx;
}
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
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
int i=0;
int m;
  //char *ptr;
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
/*send_to_gsm("ATE0\r");
send_at("AT+CSQ\r\n", "\r\n+CSQ: 29,99\r\n");
	  HAL_Delay(5000);
	  send_at("AT+CSQ\r\n", "\r\n+CSQ: 29,99\r\n");
	  	  HAL_Delay(5000);*/
int s1=0;
	  	  while (1)
	  	  {
	  //send_at("ATE0\r\n", "OK");
	 // HAL_Delay(5000);
	  //send_at("AT+CSQ\r\n", "CSQ");
	  //HAL_Delay(5000);
	  		  switch(s1)
	  		  {
	  		  case 0:
	  			m =gsm_connect_to_server();
	  			if(m==0)
	  			{
	  				s1=1;
	  			}
	  			else
	  			{
	  				s1=0;
	  			}
	  			break;
	  		  case 1:
	  			if(connect_tcp_server()==0)
	  			{
	  				s1=2;

	  			}
	  			else
	  			{
	  				s1=0;
	  			}
	  			break;
	  		case 2:
	  			if(check_server_connection()==0)
	  			{
	  				s1=3;

	  			}
	  			else
	  			{
	  				s1=1;
	  			}
	  			break;
	  		  case 3:
	  			if(send_mesg_to_server("0123456789", 50)==0)
	  			{
	  				printf("mesg send\n");
	  				s1=3;
	  			}
	  			else
	  			{
	  				s1=2;
	  			}
	  			break;
	  		  case 4:
	  			if(gsm_disconnect_to_server()==0)
	  			{
	  				s1=0;
	  			}
	  			else
	  			{
	  				s1=0;
	  			}
	  			break;
	  		  }
	  	  }
}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	 // ptr=(char *)malloc()
	 /*ptr=send_to_gsm("ATE0\r");
	 if((strncmp(ptr,"\r\nOK\r\n",6))==0)
	 {
		 printf("match found\n");
	 }
	 else
	 {
		 printf("match not found\n");
	 }
	 printf("ptr data is %s\n",ptr);
	 ptr=send_to_gsm("AT+CSQ\r\n");
	 printf("AT+CSQ ptr data is %s\n",ptr);*/
	  /*switch(state)
	  		  	  {
	  		  	  case 0:
	  		  		  switch(substate)
	  		  		  {
	  		  		  case 0:
	  		  			  str = send_to_gsm("ATE0\r");
	  		  			  if(strncmp(str,"\r\nOK\r\n",6))
	  		  			  {
	  		  				  substate=1;
	  		  			  }
	  		  			  else
	  		  			  {
	  		  				  state=1;
	  		  			  }
	  		  			  break;
	  		  		  case 1:
	  		  			  if(strncmp(str,"\r\nERROR\r\n",6))
	  		  			  {
	  		  			  	  state=0;
	  		  			  }
	  		  			  else
	  		  			  {
	  		  			  	  state=0;
	  		  			  }
	  		  			  break;
	  		  		  default:
	  		  			  break;

	  		  		  }
	  		  		  break;
	  		  	 case 1:
	  		  			  printf("success \n");
	  		  			  break;
	  		  	 default:
	  		  		 printf("default state\n");
	  		  		 break;*/
  /* USER CODE END 3 */

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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 115200;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
