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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//add this in main.c

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include <stdlib.h>


int _write(int file,char *ptr,int len)
{
	for(int i = 0  ; i < len  ; i++)
		ITM_SendChar((*ptr++));
	return len;
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char Rx_data[300];
// Define the maximum length of an NMEA sentence
#define MAX_NMEA_LENGTH 80
// Define the maximum number of JSON entries
#define MAX_JSON_ENTRIES 200 // Adjust the size as needed

int count  = 0;
// Structure to store GPS data
typedef struct {
    char time[9]; // Change to an array to store HH:MM:SS
    double latitude;
    double longitude;
    double altitude;
    // Add more fields as needed
} GPSData;

typedef struct gpsdata
{
	double time;
	float latitude;
	float longitude;
	double Knots;
	double Date;
	char N_OR_S;
	char E_OR_W;
	int fix;
	char Data[750];
	char buffer[100];
	char location[100];
}gpsdata;
uint8_t flag = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */
void GPS_receive(void);
void convertNMEATimeToIST(char *, GPSData *);
bool parseGPGGA(GPSData *);
void gpsDataToJSON(const GPSData *,char *, int, int);

#define Min_To_Degree  0.01666666667
#define Sec_To_Degree	 0.000277777778
char rx_data[60],json_str[100],*ptr;
int Flag=0;
gpsdata gps;
void gpsData(gpsdata* data);
static void gpslocation_extraction(gpsdata* data);

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
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
  char *ptr;
  int ret;

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
#if 0
    /* USER CODE END WHILE */
	  if(HAL_UART_Receive(&huart4,Rx_data,sizeof(Rx_data),1000))
	  	      {
	  	    	  printf("%s\n", Rx_data);
	  	    	//  gpsData(&gps);
	  	      }
	//  GPS_receive();
	  	if(ptr)
	  	{
	  		parseGPGGA(&gpsData);
	  	}
	  //	memset(Rx_data,'\0',sizeof(Rx_data));
	  	 HAL_Delay(1000);
    /* USER CODE BEGIN 3 */
#endif
	  	printf("in loop\n");
	  		     // HAL_UART_Receive(&huart2,gps.Data,sizeof(gps.Data),1000);
	  		     // HAL_UART_Transmit(&huart2,gps.Data,sizeof(gps.Data),1000);
	  		      if(HAL_UART_Receive(&huart4,gps.Data,sizeof(gps.Data),1000))
	  		      {
	  		    	  printf("%s\n", gps.Data);
	  		    	  gpsData(&gps);
	  		      }
	  	       	  /*HAL_UART_Receive(&huart2, rx_data,sizeof(rx_data), 1000);
	  		 	  printf("received string %s\n",rx_data);
	  		 	  //HAL_Delay(1000);
	  		 	  ptr=strstr(rx_data,"GPGGA");

	  		 	  if(ptr!=NULL)
	  		 	  {
	  		 		//uint8_t hi[10];
	  		 		//strcpy(rx_data,hi);

	  		 		//for(int i=0;rx_data[i]!='\0')
	  		 	     HAL_UART_Transmit(&huart2, rx_data, sizeof(rx_data), 100);
	  		 	  	HAL_Delay(1000);
	  		 	  	printf("transmit to serial monitor\n");
	  		 	  }

	  		 		  memset(rx_data,0,sizeof(rx_data)); */

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
  huart4.Init.BaudRate = 9600;
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
  huart2.Init.BaudRate = 9600;
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

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void GPS_receive()
{
	char *ptr;
	int ret = 0;

	// HAL_UART_Transmit(&huart2,(const uint8_t *) tx_data,6,10);
		ret= HAL_UART_Receive(&huart4, (uint8_t *)Rx_data,300, 500);
		ptr = strstr(Rx_data,"GNGGA");

		printf("\n count = %d 	msg = %s\n",count,Rx_data);
		printf("\n%s\n",Rx_data);
		if(ptr != NULL)
		{
			//printf("%s\n",Rx_data);

			flag =1;

			//memset(Rx_data, 0, sizeof(Rx_data));
			//printf("\nif ret = %d count = %d\n",ret,count);
		}
		else
		{
			printf("\nelse ret = %d count = %d\n",ret,count);
			 // memset(Rx_data, 0, sizeof(Rx_data));
		}
		  memset(Rx_data, 0, sizeof(Rx_data));
		count++;

}





void convertNMEATimeToIST(char *nmeaTime, GPSData *gpsData) {
    int hours, minutes, seconds;
    sscanf(nmeaTime, "%2d%2d%2d", &hours, &minutes, &seconds);

    // Convert to IST
    hours += 5;
    minutes += 30;

    // Adjust for overflow
    if (minutes >= 60) {
        minutes -= 60;
        hours++;
    }

    // Adjust for 24-hour clock format
    if (hours >= 24) {
        hours -= 24;
    }

    // Format and store in gpsData
    sprintf(gpsData->time, "%02d:%02d:%02d", hours, minutes, seconds);
}

// Function to parse GPGGA sentences and extract relevant information
bool parseGPGGA(GPSData *gpsData)
{
   // if (strncmp(sentence, "$GPGGA,", 7) == 0) {
        char *tokens[8];
        int tokenCount = 0;
        //char sentenceCopy[MAX_NMEA_LENGTH];
    //    strncpy(sentenceCopy, sentence, sizeof(sentenceCopy));

        char *token = strtok(Rx_data, ",");
        while (token != NULL && tokenCount < 6) {
            tokens[tokenCount++] = token;
            token = strtok(NULL, ",");
        }

        convertNMEATimeToIST(tokens[1], gpsData);

        gpsData->latitude = atof(tokens[2]);
        gpsData->longitude = atof(tokens[4]);
        gpsData->altitude = atof(tokens[9]);

      //  return true;
    //}
        flag = 0;
   // return false;
        return true;
}


void gpsData(gpsdata* data)
{
	char *P;
	int n;
	printf("in func\n");
			//HAL_UART_Receive(&GpsData->UartPort,(uint8_t*)GpsData->Data,700,HAL_MAX_DELAY);
	P=strstr(data->Data,"GNGGA");
	//printf("string found\n");
	if(*P=='G')
	{
	   n=0;
	   while(*(P+n)!='*')
	   {
		   data->location[n]=*(P+n);
		   n++;
	   }
	    printf(" string is %s", data->location);
		sprintf(data->buffer,"%s",data->location);
		sscanf(data->buffer,"GNGGA,%lf,%f,%c,%f,%c,%d,",&data->time,&data->latitude,&data->N_OR_S,&data->longitude,&data->E_OR_W,&data->fix);
		if(data->fix==1||data->fix==2||data->fix==6)
		{
			printf("valid fix\n");
			gpslocation_extraction(data);
		}
		else
		{
			printf("invalid signal no fix\n");
		}
	 }
	else
	{
		printf("no data\n");
	}
}

static void gpslocation_extraction(gpsdata* data)
{
	double Deg_Val=0.0,Min_Val=0.0,Sec_Val=0.0,lon=0.0,lat=0.0;
	int hr,min,sec;

	lon=data->longitude;
	lat=data->latitude;
	if((data->E_OR_W=='E' && data->N_OR_S=='S')||(data->E_OR_W=='W' && data->N_OR_S=='N'))
	{
		Deg_Val=(int)(lon/100);
		Min_Val=(int)(lon-(Deg_Val*100));
		Sec_Val=((lon-(Deg_Val*100))-Min_Val)*100;
		data->longitude=(Deg_Val+(Min_Val*Min_To_Degree)+(Sec_Val*Sec_To_Degree))*-1;
		printf("longitude : %f\n",data->longitude);

		Deg_Val=(int)((lat/100));
		Min_Val=(int)(lat-(Deg_Val*100));
		Sec_Val=((lat-(Deg_Val*100))-Min_Val)*10;
		data->latitude=(Deg_Val+(Min_Val*Min_To_Degree)+(Sec_Val*Sec_To_Degree));
		printf("latitude : %f\n",data->latitude);
	}
	    hr=(int)(data->time)/10000;
	    min=(int)(data->time-(hr*10000))/100;
	    sec=(int)(data->time-((hr*10000)+(min*100)));
	    //sprintf(time_buf, "%d:%d:%d",hr,min,sec);
	    printf("time: %d:%d%d\n",hr,min,sec);
	    //printf("time: %lf\n",data->time);
		sprintf(json_str,"{\"latitude\":%f,\n \"longitude\":%f,\n \"time\":%lf\n }",data->latitude, data->longitude,data->time);
		printf("json format is %s\n",json_str);

}


// Function to convert GPS data to JSON format
void gpsDataToJSON(const GPSData *gpsData, char *jsonBuffer, int bufferSize, int index)
{
    snprintf(jsonBuffer, bufferSize, "{%d: {\"time\": \"%s\", \"latitude\": %.6f, \"longitude\": %.6f, \"altitude\": %.2f}}",index, gpsData->time, gpsData->latitude, gpsData->longitude, gpsData->altitude);
    printf("%s\n",jsonBuffer);
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
