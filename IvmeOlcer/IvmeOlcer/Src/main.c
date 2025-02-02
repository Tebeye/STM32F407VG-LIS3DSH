/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "IvmeOlcereVeriGonder.h"
#include "Paketleme.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LIS3DSH_X_EKSENI_DUSUK				0x28
#define LIS3DSH_X_EKSENI_YUKSEK				0x29
#define LIS3DSH_Y_EKSENI_DUSUK				0x2A
#define LIS3DSH_Y_EKSENI_YUKSEK				0x2B
#define LIS3DSH_Z_EKSENI_DUSUK				0x2C
#define LIS3DSH_Z_EKSENI_YUKSEK				0x2D
#define IVMEOLCERBENKIMIM					0x0F
#define LIS3DSH_KONTROL_REGISTER_4			0x20 //Bu register X,Y,Z eksenlerinden veri alinacagini soylemek icin kullanildi.
#define LIS3DSH_ID							0x3F //LIS3DSH 0xOF adresine gonderilen bayt icin verecegi cevaptir.
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2S_HandleTypeDef hi2s3;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart4;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2S3_Init(void);
static void MX_SPI1_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */
//void IvmeOlcer_SPI_Okuma(uint8_t* , uint8_t , uint8_t );*/
//IvmeOlcereVeriGonder(uint8_t, uint8_t );
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
myGlobalStruct_t myGlobalStruct = {0};
uint8_t gonderilecekAdres;
uint8_t gonderilecekVeri = 0xF;
uint8_t SPI_Tx_Buffer[2];
uint16_t veriBoyutu = 1;
uint16_t veriBoyutu2 = 2;
uint8_t id;
uint8_t SPI_Rx_Buffer[2];
uint32_t sureAraligi = 40;


void IvmeOlcer_SPI_Okuma(uint8_t* veri, uint8_t adres, uint8_t sayac){

	  //Pini resetle.
	  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);
	  adres |= 0x80; //adres okumak icin en bas (MSB) 1 yapilir.
	  if(sayac > 1){
		  adres |= 0x40; // ikinci bit 1 yapilir.
	  }
	  //Adres verisini gonder.
	  HAL_SPI_Transmit(&hspi1, &gonderilecekVeri, adres, sureAraligi);
	  //Veriyi geri al.

	  HAL_SPI_Receive(&hspi1, veri, veriBoyutu2, sureAraligi);

	  //Pini set et
	  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_SET);



}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//HAL_SPI_TransmitReceive(&hspi1,&gonderilecekVeri,&alinacakVeri,veriBoyutu, sureAraligi);

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
  MX_I2S3_Init();
  MX_SPI1_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */

  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_RESET);
  SPI_Tx_Buffer [0] = LIS3DSH_KONTROL_REGISTER_4;
  SPI_Tx_Buffer [1] = 0x17;
  HAL_SPI_Transmit(&hspi1, SPI_Tx_Buffer,2,50);
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_SET);
  //////
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_RESET);
   SPI_Tx_Buffer[0] = LIS3DSH_KONTROL_REGISTER_4 | 0x80;
   HAL_SPI_Transmit(&hspi1,SPI_Tx_Buffer,1,50);

   HAL_SPI_Receive(&hspi1, SPI_Rx_Buffer,1,50);




   HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_SET);




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

/*

	  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_RESET);
	   SPI_Tx_Buffer[0] = 0x29 | 0x80;
	   HAL_SPI_Transmit(&hspi1,SPI_Tx_Buffer,1,50);

	   HAL_SPI_Receive(&hspi1, SPI_Rx_Buffer,1,50);

	   if(SPI_Rx_Buffer[0] < 50){

		   HAL_GPIO_WritePin(GPIOD, LD6_Pin, GPIO_PIN_SET );
	   }
	   else {

		   HAL_GPIO_WritePin(GPIOD, LD6_Pin, GPIO_PIN_RESET );

	   }

	   HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_SET);
	  //TM_LIS302DL_LIS3DSH_Detect();


*/
	   /////


	  /*
	   * WHO I AM OKUMA KISMI
	   */

	   HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_RESET);


	   //SPI_Tx_Buffer [0] = 0x0F;
	   SPI_Tx_Buffer [0] = IVMEOLCERBENKIMIM | 0x80;

	   HAL_SPI_Transmit(&hspi1, SPI_Tx_Buffer,1,50);
	   HAL_SPI_Receive(&hspi1, SPI_Rx_Buffer,1,50);
	   if(SPI_Rx_Buffer[0] == 0x3B){
		//   HAL_GPIO_WritePin(GPIOD, LD6_Pin, GPIO_PIN_SET );


	   }
	   else if(SPI_Rx_Buffer[0] == 0x3F) {
		//   HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_SET );


	   }

	   HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_SET);


	   	   /* WHO I AM OKUMA KISMI
	   	    	* BITIS
	   	    		*/





	   IvmeOlcerVeriOku(&hspi1,&myGlobalStruct.testIvme.testXValue[0],LIS3DSH_X_EKSENI_DUSUK,1);
	   IvmeOlcerVeriOku(&hspi1,&myGlobalStruct.testIvme.testXValue[1],LIS3DSH_X_EKSENI_YUKSEK,1);
	   myGlobalStruct.IvmeOlcerVerileri.myXValue =
			   	   ( (myGlobalStruct.testIvme.testXValue[1] << 8)* 0.06 + myGlobalStruct.testIvme.testXValue[0]* 0.06) ;

	   IvmeOlcerVeriOku(&hspi1,&myGlobalStruct.testIvme.testYValue[0],LIS3DSH_Y_EKSENI_DUSUK,1);
	   IvmeOlcerVeriOku(&hspi1,&myGlobalStruct.testIvme.testYValue[1],LIS3DSH_Y_EKSENI_YUKSEK,1);
	   myGlobalStruct.IvmeOlcerVerileri.myYValue =
			   	   ( (myGlobalStruct.testIvme.testYValue[1] << 8)* 0.06 + myGlobalStruct.testIvme.testYValue[0]* 0.06) ;

	   IvmeOlcerVeriOku(&hspi1,&myGlobalStruct.testIvme.testZValue[0],LIS3DSH_Z_EKSENI_DUSUK,1);
	   IvmeOlcerVeriOku(&hspi1,&myGlobalStruct.testIvme.testZValue[1],LIS3DSH_Z_EKSENI_YUKSEK,1);
	   myGlobalStruct.IvmeOlcerVerileri.myZValue =
			   	   ( (myGlobalStruct.testIvme.testZValue[1] << 8)* 0.06 + myGlobalStruct.testIvme.testZValue[0]* 0.06) ;

	   	   if(myGlobalStruct.IvmeOlcerVerileri.myXValue > 1916){
		   HAL_GPIO_WritePin(GPIOD,LD5_Pin, GPIO_PIN_SET);


	   }




	  // SERI ILETISIM PAKETI OLUSTURMA DOGRULAMA BYTE 0x03 olarak sectim.
	  // SERI ILETISIM PAKETI IKINCI DOGRULAMA BYTE 0x01 olarak sectim.

	   	uint8_t ilkDogrulama = 0x03;
	   	uint8_t bitisPaket = 0x0A;
	   	uint8_t ikinciDogrulama = 0x01;
	   	uint16_t paket = (ilkDogrulama << 8) ;
	   	paket |= ikinciDogrulama;
	  	HAL_UART_Transmit(&huart4,&ilkDogrulama, 1,50);
	   	HAL_UART_Transmit(&huart4,&ikinciDogrulama, 1,50);
	   	HAL_UART_Transmit(&huart4,&myGlobalStruct.testIvme.testXValue[0], 1,50);
	   	HAL_UART_Transmit(&huart4,&myGlobalStruct.testIvme.testXValue[1], 1,50);
	   	HAL_UART_Transmit(&huart4,&myGlobalStruct.testIvme.testYValue[0], 1,50);
	   	HAL_UART_Transmit(&huart4,&myGlobalStruct.testIvme.testYValue[1], 1,50);
	   	HAL_UART_Transmit(&huart4,&myGlobalStruct.testIvme.testZValue[0], 1,50);
	   	HAL_UART_Transmit(&huart4,&myGlobalStruct.testIvme.testZValue[1], 1,50);
	  //HAL_UART_Transmit(&huart4,&bitisPaket, 1,50);
	  //HAL_UART_Transmit(&huart4, myGlobalStruct.IvmeOlcerVerileri.myXValue[1], 1,50);

	  HAL_Delay(50);

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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2S3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S3_Init(void)
{

  /* USER CODE BEGIN I2S3_Init 0 */

  /* USER CODE END I2S3_Init 0 */

  /* USER CODE BEGIN I2S3_Init 1 */

  /* USER CODE END I2S3_Init 1 */
  hi2s3.Instance = SPI3;
  hi2s3.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s3.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
  hi2s3.Init.AudioFreq = I2S_AUDIOFREQ_96K;
  hi2s3.Init.CPOL = I2S_CPOL_LOW;
  hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S3_Init 2 */

  /* USER CODE END I2S3_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */
 // uint8_t myData
//  HAL_SPI_Transmit(&hspi1, 0x20C7, 16, 0);
  /* USER CODE END SPI1_Init 2 */

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
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin 
                          |Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_I2C_SPI_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin 
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin 
                          |Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_FS_Pin */
  GPIO_InitStruct.Pin = VBUS_FS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_FS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_ID_Pin OTG_FS_DM_Pin OTG_FS_DP_Pin */
  GPIO_InitStruct.Pin = OTG_FS_ID_Pin|OTG_FS_DM_Pin|OTG_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Audio_SCL_Pin Audio_SDA_Pin */
  GPIO_InitStruct.Pin = Audio_SCL_Pin|Audio_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PE0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

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
