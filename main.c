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
#define FLASH_START_ADDRESS 0x08080000

char dataToWrite[] = "hello world hello memory 25874";
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
void Write_Data_To_Flash(uint64_t address, uint64_t* data, uint64_t dataSize) {
    HAL_FLASH_Unlock();

    for (uint32_t i = 0; i < dataSize; i++) {
//        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, data[i]);
    	 FLASH_ByteProgram(FLASH_START_ADDRESS,dataToWrite );
        address += 8;
    }

    HAL_FLASH_Lock();
}

void Read_Data_From_Flash(uint64_t address, uint64_t* buffer, uint64_t dataSize) {
    for (uint32_t i = 0; i < dataSize; i++) {
        buffer[i] = *(uint64_t*)address;
        address += 8;
    }
}
void Erase_Flash_Page(uint64_t pageAddress) {
    FLASH_EraseInitTypeDef eraseConfig;
    uint32_t pageError;

    eraseConfig.TypeErase   = FLASH_TYPEERASE_PAGES;
    eraseConfig.Page        = pageAddress / FLASH_PAGE_SIZE; // Specify the page number, not the address
    eraseConfig.Banks       = FLASH_BANK_2; // Specify the bank
    eraseConfig.NbPages     = 1; // Number of pages to erase

    HAL_FLASH_Unlock();

    HAL_FLASHEx_Erase(&eraseConfig, &pageError);

    HAL_FLASH_Lock();
}

#include "stm32l4xx_hal.h"


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
 // float dataToWrite[] = {1234.5678,2019.2019,111111,222222};
  uint64_t readData[3];
//  uint64_t dataToWrite[] = {0x123,0x2019,0x111111,0x222222};
  //char gpsData[4][20] = {"02.02.24","10:59:00","8080.3456","9090.1234"};
 //char dataToWrite[] = "hello world hello memory 25874";


  /*******Erasing the page************/

        Erase_Flash_Page(FLASH_START_ADDRESS);

        /********Write data to flash*******/

        //Write_Data_To_Flash(FLASH_START_ADDRESS, dataToWrite, sizeof(dataToWrite) / sizeof(uint64_t));

       // Write_GPS_Data_To_Flash(FLASH_START_ADDRESS, gpsData, 4,20);
        int i;
for(i=0;i<80;i++)
{
       Write_Data_To_Flash(FLASH_START_ADDRESS+32*i, dataToWrite, sizeof(dataToWrite) / sizeof(uint64_t));
HAL_Delay(1000);
   	Read_Data_From_Flash(FLASH_START_ADDRESS+32*i, readData, sizeof(dataToWrite)/sizeof(uint32_t));
HAL_Delay(1000);
}

        /*********Read data from flash********/

       // Read_Data_From_Flash(FLASH_START_ADDRESS, readData, sizeof(dataToWrite) / sizeof(uint32_t));


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	Read_Data_From_Flash(FLASH_START_ADDRESS, readData, sizeof(dataToWrite)/sizeof(uint32_t));

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

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
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

// Function to convert a string to a 64-bit integer
//uint64_t stringToUint64(char* str) {
//    uint64_t result = 0;
//    size_t length = strlen(str);
//
//    // Ensure that the length does not exceed 8 bytes
//    if (length > 8) {
//        length = 8;
//    }
//
//    // Convert each character to a byte and pack them into a uint64_t
//    for (size_t i = 0; i < length; i++) {
//        result |= ((uint64_t)str[i]) << (8 * i);
//    }
//
//    return result;
//}
//void Write_GPS_Data_To_Flash(uint64_t address, char gpsData[][20], int rows, int cols) {
//    HAL_FLASH_Unlock();
//
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            uint64_t data = stringToUint64(gpsData[i][j]);
//            HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, data);
//            address += 8;
//        }
//    }
//
//    HAL_FLASH_Lock();
//}






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
