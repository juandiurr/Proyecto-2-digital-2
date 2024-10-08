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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs_sd.h"
#include "string.h"
#include "stdio.h"
#include "ili9341.h"
#include "bitmaps.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
SPI_HandleTypeDef hspi1;
FATFS fs;
FATFS *pfs;
FIL fil;
FRESULT fres;
DWORD fre_clust;
uint32_t totalSpace, freeSpace;
char buffer[100];
uint8_t start = 2;
uint8_t movex = 0;
uint8_t movex2 = 223;
uint8_t movey2 = 231;
uint8_t movey = 0;

uint8_t arriba = 0;
uint8_t abajo = 0;
uint8_t derecha = 0;
uint8_t izquierda = 0;
uint8_t arriba2 = 0;
uint8_t abajo2 = 0;
uint8_t derecha2 = 0;
uint8_t izquierda2 = 0;
uint8_t state = 3;
uint8_t linea = 0;
uint8_t linea2 = 0;
uint8_t originx = 0;
uint8_t originy = 4;
uint8_t originx2 = 0;
uint8_t originy2 = 4;
uint8_t c = 0;
uint8_t RX[1]; // Buffer para recepción de datos
const uint8_t l = 32;
const uint8_t g = 9;
const uint8_t d = 24;
uint8_t x = l;
uint8_t y = g;
uint8_t x2 = l;
uint8_t y2 = g;
uint8_t n1 = 0;//para xx, yf y yi
uint8_t n2 = 0;//para yy, xf y xi
uint8_t xx[20];
uint8_t yy[20];
uint8_t xi[20];
uint8_t xf[20];
uint8_t yi[20];
uint8_t yf[20];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM6_Init(void);
void vaciar_listas(void);
int8_t d_posicion(uint8_t arr[], uint8_t size, uint8_t numero);
int8_t d_posicion2(uint8_t arr[], uint8_t size,  uint8_t numero);
uint8_t comparacion(uint8_t num1, uint8_t num2, uint8_t numero);
uint8_t min(uint8_t num1, uint8_t num2);
uint8_t max(uint8_t num1, uint8_t num2);
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
  MX_SPI1_Init();
  MX_FATFS_Init();
  MX_USART2_UART_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, RX, 1);
  LCD_Init();
  LCD_Clear(0x00);
  //FillRect(288,0,32,8,0x1112);
  FillRect(255,0,65,300,0x630C);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //320x240
    /* USER CODE END WHILE */
	  //
	  if(state == 0){
		  HAL_Delay(2000);
		  LCD_Clear(0x0000);
		  LCD_Print("Fin Del Juego",50,90,2,0xFFFF,0x0000);
		  LCD_Print("Jugador 2 gana", 40,110,2,0xFE20,0x0000);
		  state = 1;
	  }
	  do{
		  HAL_Delay(50);
	  }while(state == 1);
	  if(state == 2){
		  vaciar_listas();
		  movex = 0;
		  movey = 0;
		  originy = 4;
		  originx = 0;
		  originy2 = 240-4;
		  originx2 = 255;
		  movex2 = 223;
		  movey2 = 231;
		  FillRect(movex,movey,x,y,0x1112);
		  x = l;
		  y = g;
		  x2 = l;
		  y2 = g;
		  FillRect(35,90,230,100,0x0000);//para tapar el "Fin del juego"
		  FillRect(255,0,65,300,0x630C);
		  arriba = 0;
		  abajo = 0;
		  derecha = 0;
		  izquierda = 0;
		  arriba2 = 0;
		  abajo2 = 0;
		  derecha2 = 0;
		  izquierda2 = 0;
		  state = 3;
	  }
	  do{
		  FillRect(movex,movey,x,y,0x1112);//jugador 1(azul)
		  FillRect(movex2,movey2,x2,y2,0xFE20);//jugador 2 (amarillo)
		  HAL_Delay(50);
			  if(movex < 0 || movex > 255-l){
				  state = 0;
			  }
			  if(movey < 0 || movey > 240-l){
				  state = 0;
			  }
			  /*if(movex2 < 0 || movex2 > 255-l){
				  state = 0;
			  }
			  if(movey2 < 0 || movey2 > 240-l){
				  state = 0;
			  }*/
			  //*****************************************************************************
			  //******************************JUGADOR 1**************************************
			  //*****************************************************************************
			  if (arriba == 2){

				  int8_t oi = 0;
				  oi = d_posicion(yy, n2, movey);
				  if (oi != -1){
					  //FillRect(288,0,32,300,0xF800);
					  //HAL_Delay(100);
					  //illRect(288,0,32,300,0x630C);
					  uint8_t i;
					  uint8_t f;
					  uint8_t io;

					  i = xi[oi];
					  f = xf[oi];
					  oi = comparacion(i,f,movex);
					  io = comparacion(i,f,movex+g);
					  if(oi == 1 || io == 1){
						  state = 0;
					  }
				  }
				  movey -= 4;
				  linea+=4;
				  V_line(originx,movey+l,linea,0xFFFF);
				  FillRect(movex,movey+l,2,4,0x0000);
				  FillRect(movex+2,movey+l,2,4,0x023F);
				  //FillRect(movex+4,movey+l,1,4,0xFFFF);

				  FillRect(movex+5,movey+l,2,4,0x023F);
				  FillRect(movex+7,movey+l,2,4,0x0000);
				  if (c == 1){
					  /*uint8_t oi = 0;
					  oi = d_posicion2(yy, n2, movey);
					  if (oi != -1){
						  //FillRect(288,0,32,300,0xF800);
						  //HAL_Delay(100);
						  //FillRect(288,0,32,300,0x630C);
						  uint8_t i;
						  uint8_t f;
						  uint8_t io;
						  i = xi[oi];
						  f = xf[oi];
						  oi = comparacion(i,f,movex);
						  io = comparacion(i,f,movex+g);
						  if(oi == 1 || io == 1){
							state = 0;
						  }
					  }*/
					  c = 0;
				  }
			  }
			  if (abajo == 2){
				  int8_t oi = 0;
				  oi = d_posicion(yy, n2, movey+l);
				  if (oi != -1){
					  //FillRect(288,0,32,300,0xF800);
					  //HAL_Delay(100);
					  //illRect(288,0,32,300,0x630C);
					  uint8_t i;
					  uint8_t f;
					  uint8_t io;

					  i = xi[oi];
					  f = xf[oi];
					  oi = comparacion(i,f,movex);
					  io = comparacion(i,f,movex+g);
					  if(oi == 1 || io == 1){
						  state = 0;
					  }
				  }
				  movey += 4;
				  linea+=4;
				  V_line(originx,originy,linea,0xFFFF);
				  FillRect(movex,movey-4,2,4,0x0000);
				  FillRect(movex+2,movey-4,2,4,0x023F);
				  //FillRect(movex+4,movey-4,1,4,0xFFFF);
				  FillRect(movex+5,movey-4,2,4,0x023F);
				  FillRect(movex+7,movey-4,2,4,0x0000);
			  }
			  if (derecha == 2){
				  int8_t oi = 0;
				  oi = d_posicion(xx, n1, movex+l);
				  if (oi != -1){
					  //FillRect(288,0,32,300,0xF800);
					  //HAL_Delay(100);
					  //illRect(288,0,32,300,0x630C);
					  uint8_t i;
					  uint8_t f;
					  uint8_t io;

					  i = yi[oi];
					  f = yf[oi];
					  oi = comparacion(i,f,movey);
					  io = comparacion(i,f,movey+g);
					  if(oi == 1 || io == 1){
						  state = 0;
					  }
				  }
				  movex += 4;
				  linea+=4;
				  H_line(originx,originy,linea,0xFFFF);
				  FillRect(movex-4,movey,4,2,0x0000);
				  FillRect(movex-4,movey+2,4,2,0x023F);
				  //FillRect(movex-4,movey+4,4,1,0xFFFF);
				  FillRect(movex-4,movey+5,4,2,0x023F);
				  FillRect(movex-4,movey+7,4,2,0x0000);
			  }
			  if (izquierda == 2){
				  int8_t oi = 0;
				  oi = d_posicion(xx, n1, movex);
				  if (oi != -1){
					  //FillRect(288,0,32,300,0xF800);
					  //HAL_Delay(100);
					  //illRect(288,0,32,300,0x630C);
					  uint8_t i;
					  uint8_t f;
					  uint8_t io;

					  i = yi[oi];
					  f = yf[oi];
					  oi = comparacion(i,f,movey);
					  io = comparacion(i,f,movey+g);
					  if(oi == 1 || io == 1){
						  state = 0;
					  }
				  }
				  movex -= 4;
				  linea+=4;
				  H_line(movex+l,originy,linea,0xFFFF);
				  FillRect(movex+l,movey,4,2,0x0000);
				  FillRect(movex+l,movey+2,4,2,0x023F);
				  //FillRect(movex+l,movey+4,4,1,0xFFFF);
				  FillRect(movex+l,movey+5,4,2,0x023F);
				  FillRect(movex+l,movey+7,4,2,0x0000);

			  }
			  //******************************************************************************
			  //******************************JUGADOR 2***************************************
			  //*******************************************************************************
			  if (arriba2 == 2){
				  int8_t oi = 0;
				  oi = d_posicion(yy, n2, movey2);
				  if (oi != -1){
					  //FillRect(288,0,32,300,0xF800);
					  //HAL_Delay(100);
					  //illRect(288,0,32,300,0x630C);
					  uint8_t i;
					  uint8_t f;
					  uint8_t io;

					  i = xi[oi];
					  f = xf[oi];
					  oi = comparacion(i,f,movex2);
					  io = comparacion(i,f,movex2+g);
					  if(oi == 1 || io == 1){
						  state = 5;
					  }
				  }
				  movey2 -= 4;
				  linea2+=4;
				  V_line(originx2,movey2+l,linea2,0xFFFF);
				  FillRect(movex2,movey2+l,2,4,0x0000);
				  FillRect(movex2+2,movey2+l,2,4,0xCE00);
				  //FillRect(movex+4,movey+l,1,4,0xFFFF);
				  FillRect(movex2+5,movey2+l,2,4,0xCE00);
				  FillRect(movex2+7,movey2+l,2,4,0x0000);
				  if (c == 1){

					  c = 0;
				  }
			  }
			  if (abajo2 == 2){
				  int8_t oi = 0;
				  oi = d_posicion(yy, n2, movey2+l);
				  if (oi != -1){
					  //FillRect(288,0,32,300,0xF800);
					  //HAL_Delay(100);
					  //illRect(288,0,32,300,0x630C);
					  uint8_t i;
					  uint8_t f;
					  uint8_t io;

					  i = xi[oi];
					  f = xf[oi];
					  oi = comparacion(i,f,movex2);
					  io = comparacion(i,f,movex2+g);
					  if(oi == 1 || io == 1){
						  state = 5;
					  }
				  }
				  movey2 += 4;
				  linea2+=4;
				  V_line(originx2,originy2,linea2,0xFFFF);
				  FillRect(movex2,movey2-4,2,4,0x0000);
				  FillRect(movex2+2,movey2-4,2,4,0xCE00);
				  //FillRect(movex+4,movey-4,1,4,0xFFFF);
				  FillRect(movex2+5,movey2-4,2,4,0xCE00);
				  FillRect(movex2+7,movey2-4,2,4,0x0000);
			  }
			  if (derecha2 == 2){
				  int8_t oi = 0;
				  oi = d_posicion(xx, n1, movex2+l);
				  if (oi != -1){
					  //FillRect(288,0,32,300,0xF800);
					  //HAL_Delay(100);
					  //illRect(288,0,32,300,0x630C);
					  uint8_t i;
					  uint8_t f;
					  uint8_t io;

					  i = yi[oi];
					  f = yf[oi];
					  oi = comparacion(i,f,movey2);
					  io = comparacion(i,f,movey2+g);
					  if(oi == 1 || io == 1){
						  state = 5;
					  }
				  }
				  movex2 += 4;
				  linea2+=4;
				  H_line(originx2,originy2,linea2,0xFFFF);
				  FillRect(movex2-4,movey2,4,2,0x0000);
				  FillRect(movex2-4,movey2+2,4,2,0xCE00);
				  //FillRect(movex-4,movey+4,4,1,0xFFFF);
				  FillRect(movex2-4,movey2+5,4,2,0xCE00);
				  FillRect(movex2-4,movey2+7,4,2,0x0000);
			  }
			  if (izquierda2 == 2){
				  int8_t oi = 0;
				  oi = d_posicion(xx, n1, movex2);
				  if (oi != -1){
					  //FillRect(288,0,32,300,0xF800);
					  //HAL_Delay(100);
					  //illRect(288,0,32,300,0x630C);
					  uint8_t i;
					  uint8_t f;
					  uint8_t io;

					  i = yi[oi];
					  f = yf[oi];
					  oi = comparacion(i,f,movey2);
					  io = comparacion(i,f,movey2+g);
					  if(oi == 1 || io == 1){
						  state = 5;
					  }
				  }
				  movex2 -= 4;
				  linea2+=4;
				  H_line(movex2+l,originy2,linea2,0xFFFF);
				  FillRect(movex2+l,movey2,4,2,0x0000);
				  FillRect(movex2+l,movey2+2,4,2,0xCE00);
				  //FillRect(movex+l,movey+4,4,1,0xFFFF);
				  FillRect(movex2+l,movey2+5,4,2,0xCE00);
				  FillRect(movex2+l,movey2+7,4,2,0x0000);

			  }
	  }while(state == 3);

	  //FillRect(movex,movey,20,10,0x023F);
	  if(state == 5){
		  HAL_Delay(2000);
		  LCD_Clear(0x0000);
		  LCD_Print("Fin Del Juego",50,90,2,0xFFFF,0x0000);
		  LCD_Print("Jugador 1 gana", 40,110,2,0x1112,0x0000);
		  do{
			  HAL_Delay(50);
		  }while(state == 5);
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 128;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 3036;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LCD_RST_Pin|LCD_D1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_RD_Pin|LCD_WR_Pin|LCD_RS_Pin|LCD_D7_Pin
                          |LCD_D0_Pin|LCD_D2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin|LCD_D6_Pin|LCD_D3_Pin|LCD_D5_Pin
                          |LCD_D4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SD_SS_GPIO_Port, SD_SS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LCD_RST_Pin LCD_D1_Pin */
  GPIO_InitStruct.Pin = LCD_RST_Pin|LCD_D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RD_Pin LCD_WR_Pin LCD_RS_Pin LCD_D7_Pin
                           LCD_D0_Pin LCD_D2_Pin */
  GPIO_InitStruct.Pin = LCD_RD_Pin|LCD_WR_Pin|LCD_RS_Pin|LCD_D7_Pin
                          |LCD_D0_Pin|LCD_D2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_CS_Pin LCD_D6_Pin LCD_D3_Pin LCD_D5_Pin
                           LCD_D4_Pin SD_SS_Pin */
  GPIO_InitStruct.Pin = LCD_CS_Pin|LCD_D6_Pin|LCD_D3_Pin|LCD_D5_Pin
                          |LCD_D4_Pin|SD_SS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
uint8_t min(uint8_t num1, uint8_t num2){
	return (num1<num2) ? num1:num2;
}
uint8_t max(uint8_t num1, uint8_t num2){
	return (num1>num2) ? num1:num2;
}
uint8_t comparacion(uint8_t num1, uint8_t num2, uint8_t numero){
	uint8_t minimo;
	uint8_t maximo;
	minimo = min(num1,num2);
	maximo = max(num1,num2);
	if (numero >= minimo && numero <= maximo){
		return 1;
	}
	return 0;
}
int8_t d_posicion(uint8_t arr[], uint8_t size, uint8_t numero){
	uint8_t i = 0;
	for(i = 0; i <= size; i++){
		if (arr[i] >= numero-5 && arr[i] <= numero){
			return i;
		}
	}
	return -1;
}
int8_t d_posicion2(uint8_t arr[], uint8_t size,  uint8_t numero){//arriba y derecha
	uint8_t i = 0;
	for(i = 0; i <= size; i++){
		if (numero >= arr[i] && numero <= arr[i] + l - 5){
			return i;
		}
	}
	return -1;
}

void vaciar_listas(void){
	for(int i = 0; i <= n2; i++){
		yy[i] = 0;
		xi[i] = 0;
		xf[i] = 0;
	}
	for(int i = 0; i <= n1; i++){
		xx[i] = 0;
		yi[i] = 0;
		yf[i] = 0;
	}
	n1 = 0;
	n2 = 0;

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	c = 1;

	if(RX[0] == 'e'){
		if(state == 1 || state == 5){
			state = 2;
		}

	}
	if(RX[0] == 'w'){//arriba
		n2++;
		linea = 0;
		FillRect(movex,movey,x,2,0x0000);
		FillRect(movex,movey+2,x,2,0x023F);
		FillRect(movex,movey+4,x,1,0xFFFF);
		FillRect(movex,movey+5,x,2,0x023F);
		FillRect(movex,movey+7,x,2,0x0000);
		x = g;
		y = l;
		if (abajo != 2){
			arriba = 2;
		}

		if (derecha != 0){
			derecha--;
		}
		if (abajo != 0){
			abajo--;
		}

		if (izquierda != 0){
			izquierda--;
		}

		if (derecha == 1){

			yy[n2] = movey + 4;
			xf[n2] = movex+d+4;
			xi[n2] = xx[n1];

			originx = movex+d+4;
			movex = movex + d;
			movey = movey - d;

		}
		if (izquierda == 1){

			yy[n2] = movey+4;
			xf[n2] = movex+4;
			xi[n2] = xx[n1];

			originx = movex+4;
			movey = movey - d;
		}

	}
	if(RX[0] == 's'){//abajo
		n2++;
		linea = 0;
		FillRect(movex,movey,x,2,0x0000);
		FillRect(movex,movey+2,x,2,0x023F);
		FillRect(movex,movey+4,x,1,0xFFFF);
		FillRect(movex,movey+5,x,2,0x023F);
		FillRect(movex,movey+7,x,2,0x0000);
		x = g;
		y = l;

		if (arriba != 2){
			abajo = 2;
		}

		if (arriba != 0){
			arriba--;
		}
		if (derecha != 0){
			derecha--;
		}

		if (izquierda != 0){
			izquierda--;
		}

		if (derecha == 1){
			yy[n2] = movey + 4;
			xf[n2] = movex+d+4;
			xi[n2] = xx[n1];
			H_line(xi[n2],yy[n2],abs(xf[n2]-xi[n2]),0xFFFF);


			originx=movex+d+4;
			originy=movey;
			movex = movex + d;
		}
		if(izquierda == 1){

			yy[n2] = movey+4;
			xf[n2] = movex+4;
			xi[n2] = xx[n1];
			H_line(xf[n2],yy[n2],abs(xf[n2]-xi[n2]),0xFFFF);
			originx=movex+4;
			originy = movey;
		}

	}
	if(RX[0] == 'a'){//izquierda
		linea = 0;
		n1++;
		FillRect(movex,movey,2,y,0x0000);
		FillRect(movex+2,movey,2,y,0x023F);
		FillRect(movex+4,movey,1,y,0xFFFF);
		FillRect(movex+5,movey,2,y,0x023F);
		FillRect(movex+7,movey,2,y,0x0000);
		y = g;
		x = l;
		if (derecha != 2){
			izquierda = 2;
		}

		if (arriba != 0){
			arriba--;
		}
		if (abajo != 0){
			abajo--;
		}

		if (derecha != 0){
			derecha--;
		}

		if (arriba == 1){

			xx[n1] = movex+4;
			yf[n1] = movey + 4;
			yi[n1] = yy[n2];

			movex = movex - d;
			originy = movey+4;

		}
		if (abajo == 1){

			xx[n1] = movex+4;
			yf[n1] = movey+d+4;
			yi[n1] = yy[n2];

			originy = movey+d+4;

			movex = movex - d;
			movey = movey + d;
		}
	}
	if(RX[0] == 'd'){//derecha
		linea = 0;
		n1++;
		FillRect(movex,movey,2,y,0x0000);
		FillRect(movex+2,movey,2,y,0x023F);
		FillRect(movex+4,movey,1,y,0xFFFF);
		FillRect(movex+5,movey,2,y,0x023F);
		FillRect(movex+7,movey,2,y,0x0000);
		x = l;
		y = g;

		if (izquierda != 2){
			derecha = 2;
		}

		if (arriba != 0){
			arriba--;
		}
		if (abajo != 0){
			abajo--;
		}

		if (izquierda != 0){
			izquierda--;
		}
		if (abajo == 1){

			xx[n1] = movex+4;
			yf[n1] = movey+d+4;
			yi[n1] = yy[n2];

			originy=movey+4+d;
			movey = movey + d;
			originx = movex;

		}
		if(arriba == 1){

			xx[n1] = movex+4;
			yf[n1] = movey + 4;
			yi[n1] = yy[n2];

			originy = movey+4;
			originx = movex;
		}
	}

//************************************************************************************************
//***********************************Jugador 2****************************************************
//************************************************************************************************
	if(RX[0] == 'y'){//arriba j2
		n2++;
		linea2 = 0;
		FillRect(movex2,movey2,x2,2,0x0000);
		FillRect(movex2,movey2+2,x2,2,0xCE00);
		FillRect(movex2,movey2+4,x2,1,0xFFFF);
		FillRect(movex2,movey2+5,x2,2,0xCE00);
		FillRect(movex2,movey2+7,x2,2,0x0000);
		x2 = g;
		y2 = l;
		if (abajo2 != 2){
			arriba2 = 2;
		}

		if (derecha2 != 0){
			derecha2--;
		}
		if (abajo2 != 0){
			abajo2--;
		}

		if (izquierda2 != 0){
			izquierda2--;
		}

		if (derecha2 == 1){

			yy[n2] = movey2 + 4;
			xf[n2] = movex2+d+4;
			xi[n2] = xx[n1];

			originx2 = movex2+d+4;
			movex2 = movex2 + d;
			movey2 = movey2 - d;

		}
		if (izquierda2 == 1){

			yy[n2] = movey2+4;
			xf[n2] = movex2+4;
			xi[n2] = xx[n1];

			originx2 = movex2+4;
			movey2 = movey2 - d;
		}

	}
	if(RX[0] == 'h'){//abajo j2
		n2++;
		linea2 = 0;
		FillRect(movex2,movey2,x2,2,0x0000);
		FillRect(movex2,movey2+2,x2,2,0xCE00);
		FillRect(movex2,movey2+4,x2,1,0xFFFF);
		FillRect(movex2,movey2+5,x2,2,0xCE00);
		FillRect(movex2,movey2+7,x2,2,0x0000);
		x2 = g;
		y2 = l;

		if (arriba2 != 2){
			abajo2 = 2;
		}

		if (arriba2 != 0){
			arriba2--;
		}
		if (derecha2 != 0){
			derecha2--;
		}

		if (izquierda2 != 0){
			izquierda2--;
		}

		if (derecha2 == 1){
			yy[n2] = movey2 + 4;
			xf[n2] = movex2+d+4;
			xi[n2] = xx[n1];
			H_line(xi[n2],yy[n2],abs(xf[n2]-xi[n2]),0xFFFF);


			originx2=movex2+d+4;
			originy2=movey2;
			movex2 = movex2 + d;
		}
		if(izquierda == 1){

			yy[n2] = movey2+4;
			xf[n2] = movex2+4;
			xi[n2] = xx[n1];
			H_line(xf[n2],yy[n2],abs(xf[n2]-xi[n2]),0xFFFF);
			originx2=movex2+4;
			originy2 = movey2;
		}
	}
	if(RX[0] == 'j'){//derecha j2
		linea2 = 0;
		n1++;
		FillRect(movex2,movey2,2,y2,0x0000);
		FillRect(movex2+2,movey2,2,y2,0xCE00);
		FillRect(movex2+4,movey2,1,y2,0xFFFF);
		FillRect(movex2+5,movey2,2,y2,0xCE00);
		FillRect(movex2+7,movey2,2,y2,0x0000);
		x2 = l;
		y2 = g;

		if (izquierda2 != 2){
			derecha2 = 2;
		}

		if (arriba2 != 0){
			arriba2--;
		}
		if (abajo2 != 0){
			abajo2--;
		}

		if (izquierda2 != 0){
			izquierda2--;
		}
		if (abajo2 == 1){

			xx[n1] = movex2+4;
			yf[n1] = movey2+d+4;
			yi[n1] = yy[n2];

			originy2=movey2+4+d;
			movey2 = movey2 + d;
			originx2 = movex2;

		}
		if(arriba2 == 1){

			xx[n1] = movex2+4;
			yf[n1] = movey2 + 4;
			yi[n1] = yy[n2];

			originy2 = movey2+4;
			originx2 = movex2;
		}
	}
	if(RX[0] == 'g'){//izquierda j2
		linea2 = 0;
		n1++;
		FillRect(movex2,movey2,2,y2,0x0000);
		FillRect(movex2+2,movey2,2,y2,0xCE00);
		FillRect(movex2+4,movey2,1,y2,0xFFFF);
		FillRect(movex2+5,movey2,2,y2,0xCE00);
		FillRect(movex2+7,movey2,2,y2,0x0000);
		y2 = g;
		x2 = l;
		if (derecha2 != 2){
			izquierda2 = 2;
		}

		if (arriba2 != 0){
			arriba2--;
		}
		if (abajo2 != 0){
			abajo2--;
		}

		if (derecha2 != 0){
			derecha2--;
		}

		if (arriba2 == 1){

			xx[n1] = movex2+4;
			yf[n1] = movey2 + 4;
			yi[n1] = yy[n2];

			movex2 = movex2 - d;
			originy2 = movey2+4;

		}
		if (abajo2 == 1){

			xx[n1] = movex2+4;
			yf[n1] = movey2+d+4;
			yi[n1] = yy[n2];

			originy2 = movey2+d+4;

			movex2 = movex2 - d;
			movey2 = movey2 + d;
		}
	}

	HAL_UART_Receive_IT(&huart2, RX, 1);
}
/*void TIM6_DAC_IRQHandler(void){
	if (movex < 200 && movey == 33){
		movex++;
	}else if(movex == 200){
		movey++;
	}
	if(movey == 150){
		movex = 200;
		movey = 150;
	}
	HAL_TIM_IRQHandler(&htim6);
}*/
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
