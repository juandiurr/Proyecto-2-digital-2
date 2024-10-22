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
//#include "SD.h"
//#include "pgmspace.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//#define MAX_FILE_SIZE 100000
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/*SPI_HandleTypeDef hspi1;
FATFS fs;
FATFS *pfs;
FIL fil;
FRESULT fres;
DWORD fre_clust;
uint32_t totalSpace, freeSpace;
char buffer[100];*/

//unsigned char menu[MAX_FILE_SIZE] PROGMEM;
//extern uint8_t menu2[];
extern uint8_t logo[];
extern uint8_t moto_[];

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
uint8_t state = 6;

uint8_t c = 0;
uint8_t RX[1]; // Buffer para recepción de datos

const uint8_t l = 32;
const uint8_t g = 9;
const uint8_t d = 24;
const uint8_t mm = 5;

const uint16_t rosa = 0xF97A;
const uint16_t verde = 	0x06A0;
const uint16_t rojo = 0xE863;
const uint16_t naranja = 0xF3C0;
const uint16_t azul = 0x023F;
const uint16_t amarillo = 0xD6A0;

const uint16_t azulo = 0x1112;
const uint16_t amarilloo = 0xFE20;
const uint16_t rosao = 	0xD218;
const uint16_t verdeo = 0x0D61;
const uint16_t rojoo = 0xB000;
const uint16_t naranjao = 0xD320;

const uint8_t pr = 7;
uint8_t x = l;
uint8_t y = g;
uint8_t x2 = l;
uint8_t y2 = g;
int8_t n1 = -1;//para xx, yf y yi
int8_t n2 = -1;//para yy, xf y xi
int8_t n3 = -1;//para xx2, yf y yi
int8_t n4 = -1;//para yy2, xf y xi
uint8_t io = 0;
uint8_t xx[20];
uint8_t yy[20];
uint8_t xi[20];
uint8_t xf[20];
uint8_t yi[20];
uint8_t yf[20];
uint8_t xx2[20];
uint8_t yy2[20];
uint8_t xi2[20];
uint8_t xf2[20];
uint8_t yi2[20];
uint8_t yf2[20];

uint16_t rastroj1 = azul;
uint16_t rastroj2 = amarillo;
uint16_t colorj1 = 0;
uint16_t colorj2 = 0;

int8_t vj1 = 4;
int8_t vj2 = 4;
int8_t j1[2];
int8_t j2[2];
int8_t gj2 = -1;
int8_t gj1 = -1;

uint8_t turbo1 = 0;
uint8_t turbo2 = 0;
uint8_t cd1 = 0;
uint8_t cd2 = 0;
char tm1[4];
char tm2[0];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim13;
TIM_HandleTypeDef htim14;

UART_HandleTypeDef huart5;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_UART5_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM14_Init(void);
static void MX_TIM13_Init(void);
/* USER CODE BEGIN PFP */

void vaciar_listas(void);
int8_t d_posicion(uint8_t arr[], uint8_t size, uint8_t numero);
int8_t d_posicion2(uint8_t arr[], uint8_t size, uint8_t numero, uint8_t velocidad);
int8_t d_posicion3(uint8_t arr[], uint8_t size, uint8_t numero,uint8_t numero2);
uint8_t comparacion(uint8_t num1, uint8_t num2, uint8_t numero);
uint8_t min(uint8_t num1, uint8_t num2);
uint8_t max(uint8_t num1, uint8_t num2);
void j1borrar(void);
void j2borrar(void);
void cool1(void);
void cool2 (void);
void transmit_uart(char *message);
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
  MX_UART5_Init();
  MX_USART2_UART_Init();
  MX_TIM14_Init();
  MX_TIM13_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, RX, 1);
  //UHAL_TIM_Base_Stop_IT(&htim14);

  LCD_Init();
  //LCD_Clear(0x00);
  //FillRect(288,0,32,8,0x1112);
  //FillRect(255,0,65,300,0x630C);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //320x240
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(state == 0){
	  		  char buffer[4];
	  		  transmit_uart("3");
	  		  FillRect(movex,movey,x,y,colorj1);//jugador 1(azul)
	  		  FillRect(movex2,movey2,x2,y2,colorj2);//jugador 2 (amarillo)
	  		  if(derecha2 == 2){
				  LCD_Bitmap(movex2+pr,movey2,18,9,moto_derecha);

			  }
			  if(izquierda2 == 2){
				  LCD_Bitmap(movex2+pr,movey2,18,9,moto_izquierda);

			  }
			  if(abajo2 == 2){
				  LCD_Bitmap(movex2,movey2+pr,9,18,moto_abajo);

			  }
			  if(arriba2 == 2){
				  LCD_Bitmap(movex2,movey2+pr,9,18,moto_arriba);

			  }
	  		  if(derecha == 2){
	  			  LCD_Bitmap(movex+pr,movey,18,9,moto_derecha);
	  			  LCD_Sprite(movex+20,movey-4,20,16,explosion,5,0,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex+20,movey-4,20,16,explosion,5,1,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex+20,movey-4,20,16,explosion,5,2,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex+20,movey-4,20,16,explosion,5,3,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex+20,movey-4,20,16,explosion,5,4,0,0);
				  HAL_Delay(150);
	  		  }
	  		  if(izquierda == 2){
	  			  LCD_Bitmap(movex+pr,movey,18,9,moto_izquierda);
	  			  LCD_Sprite(movex-8,movey-4,20,16,explosion,5,0,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-8,movey-4,20,16,explosion,5,1,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-8,movey-4,20,16,explosion,5,2,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-8,movey-4,20,16,explosion,5,3,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-8,movey-4,20,16,explosion,5,4,0,0);
				  HAL_Delay(150);
	  		  }
	  		  if(abajo == 2){
	  			  LCD_Bitmap(movex,movey+pr,9,18,moto_abajo);
	  			  LCD_Sprite(movex-6,movey+20,20,16,explosion,5,0,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-6,movey+20,20,16,explosion,5,1,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-6,movey+20,20,16,explosion,5,2,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-6,movey+20,20,16,explosion,5,3,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-6,movey+20,20,16,explosion,5,4,0,0);
				  HAL_Delay(150);
	  		  }
	  		  if(arriba == 2){
	  			  LCD_Bitmap(movex,movey+pr,9,18,moto_arriba);
	  			  LCD_Sprite(movex-6,movey-8,20,16,explosion,5,0,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-6,movey-8,20,16,explosion,5,1,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-6,movey-8,20,16,explosion,5,2,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-6,movey-8,20,16,explosion,5,3,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex-6,movey-8,20,16,explosion,5,4,0,0);
				  HAL_Delay(150);
	  		  }

	  		  HAL_Delay(2000);
	  		  LCD_Clear(0x0000);
	  		  LCD_Print("Fin Del Juego",50,90,2,0xFFFF,0x0000);
	  		  LCD_Print("Jugador 2 gana", 40,110,2,rastroj2,0x0000);
	  		  gj2++;
	  		  sprintf(buffer, "%u",gj2);
	  		  LCD_Print(buffer, 175,130,2,rastroj2,0x0000);
	  		  LCD_Print("-", 160,130,2,0xFFFF,0x0000);
	  		  sprintf(buffer, "%u",gj1);
	  		  if(gj2 == 0){
	  			  LCD_Print("0",145,130,2,rastroj1,0x0000);
	  		  }else{
	  			  LCD_Print(buffer,145,130,2,rastroj1,0x0000);
	  		  }

	  		  do{
	  			  HAL_Delay(50);
	  		  }while(state == 0);
	  	  }else if(state == 2){

	  		  vaciar_listas();
	  		  movex = 0;
	  		  movey = 0;

	  		  movex2 = 0;
	  		  movey2 = 240-g;
	  		  x = l;
	  		  y = g;
	  		  x2 = l;
	  		  y2 = g;
	  		  FillRect(35,90,230,100,0x0000);//para tapar el "Fin del juego"
	  		  FillRect(255,0,2,240,azul);
	  		  FillRect(257,0,1,240,0xFFFF);
	  		  FillRect(258,0,2,240,azul);
	  		  V_line(32,0,240,0x212E);
	  		  V_line(64,0,240,0x212E);
	  		  V_line(96,0,240,0x212E);
	  		  V_line(128,0,240,0x212E);
	  		  V_line(160,0,240,0x212E);
	  		  V_line(192,0,240,0x212E);
	  		  V_line(224,0,240,0x212E);
	  		  H_line(0,32,255,0x212E);
	  		  H_line(0,64,255,0x212E);
	  		  H_line(0,96,255,0x212E);
	  		  H_line(0,128,255,0x212E);
	  		  H_line(0,160,255,0x212E);
	  		  H_line(0,192,255,0x212E);
	  		  H_line(0,224,255,0x212E);
	  		  arriba = 0;
	  		  abajo = 0;
	  		  derecha = 2;
	  		  izquierda = 0;
	  		  arriba2 = 0;
	  		  abajo2 = 0;
	  		  derecha2 = 2;
	  		  izquierda2 = 0;
	  		  HAL_Delay(100);
	  		  state = 3;
	  	  }else if(state == 3){
	  		  transmit_uart("2");
	  		  cd1 = 0;
	  		  cd2 = 0;
	  		  do{

	  			  HAL_Delay(50);
	  			  if(cd1 <= 8 && cd1 >= 6){
					  vj1 = 8;
				  }else{
					  vj1 = 4;
				  }
	  			  cool1();
	  			  if(cd2 <= 8 && cd2 >= 6){
	  				  vj2 = 8;
	  			  }else{
	  				  vj2 = 4;
	  			  }
	  			  cool2();


	  			  if(x == l){
	  				  if(movex < 0 || movex > 255-l){
	  					  state = 0;
	  				  }
	  			  }else if(x == g){
	  				  if(movey < 0 || movey > 240-l){
	  					  state = 0;
	  				  }
	  			  }
	  			  if(x2 == l){
	  				  if(movex2 < 0 || movex2 > 255-l){
	  					  //FillRect(0,0,30,60,rosa);
	  					  state = 5;
	  				  }
	  			  }else if(x2 == g){
	  				  if(movey2 < 0 || movey2 > 240-l){
	  					  //FillRect(0,0,30,60,rosa);
	  					  state = 5;
	  				  }
	  			  }


	  			  //*****************************************************************************
	  			  //******************************JUGADOR 1**************************************
	  			  //*****************************************************************************

	  			  if (arriba == 2){
	  				  FillRect(movex,movey,x,y,colorj1);//jugador 1(azul)
	  				  LCD_Bitmap(movex,movey+pr,9,18,moto_arriba);
	  				  //COLISION DE LOS RASTROS QUE DEJA EL JUGADOR
	  				  int8_t oi = 0;
	  				  oi = d_posicion3(yy, n2, movey,movey-vj1);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = xi[oi];
	  					  f = xf[oi];
	  					  oi = comparacion(i,f,movex);
	  					  iio = comparacion(i,f,movex+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 0;
	  					  }
	  				  }
	  				  oi = d_posicion3(yy2, n4, movey,movey-vj1);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = xi2[oi];
	  					  f = xf2[oi];
	  					  oi = comparacion(i,f,movex);
	  					  iio = comparacion(i,f,movex+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 0;
	  					  }
	  				  }


	  				  //COLISION CUANDO EL JUGADOR SE MUEVE
	  				  if(izquierda2 == 2){
	  					  io = comparacion(movex2,movex2-(vj2),movex+4);
	  					  if(io == 1){
	  						  //FillRect(255,0,65,300,0xFFFF);
	  						  //HAL_Delay(100);
	  						  //FillRect(255,0,65,300,0x630C);
	  						  io = comparacion(movey, yy[n2], movey2);
	  						  if(io == 1){
	  							  state = 5;
	  							  //FillRect(movex+4,movey2,0xFE20);
	  						  }

	  						  io = comparacion(movey, yy[n2], movey2+g);
	  						  if(io == 1){
	  							  state = 5;
	  						  }
	  					  }
	  				  }
	  				  if(derecha2 == 2){
	  					  io = comparacion(movex2+l+vj2,movex2+l,movex+4);
	  					  if(io == 1){
	  						  io = comparacion(movey, yy[n2], movey2);
	  						  if(io == 1){
	  							  state = 5;
	  						  }
	  						  io = comparacion(movey,yy[n2],movey+g);
	  						  if(io == 1){
	  							  state = 5;
	  						  }
	  					  }

	  				  }
	  				  //CUANDO EL JUGADOR CRUZA
	  				  if(c == 1){
	  					  int8_t i=0;
	  					  uint8_t o=0;
	  					  i = d_posicion3(yy,n2,movey+l-mm,movey);
	  					  if(i != -1){
	  						  o = comparacion(xf[i], xi[i], movex);
	  						  if (o == 1){
	  							  state = 0;
	  						  }
	  						  o = comparacion(xf[i], xi[i], movex+g);
	  						  if(o==1){
	  							  state = 0;
	  						  }
	  					  }
	  					  i = d_posicion3(yy2,n4,movey+l-mm,movey);
	  					  if(i != -1){
	  						  o = comparacion(xf2[i], xi2[i], movex);
	  						  if (o == 1){
	  							  state = 0;
	  						  }
	  						  o = comparacion(xf2[i], xi2[i], movex+g);
	  						  if(o==1){
	  							  state = 0;
	  						  }
	  					  }
	  					  if(izquierda2 == 2){
	  						  i = comparacion(movey,movey+l-mm,movey2+4);
	  						  if(i == 1){
	  							  o = comparacion(movex2,xx2[n3],movex);
	  							  if (o == 1){
	  								  state = 0;
	  							  }
	  							  o = comparacion(movex2,xx2[n3],movex+g);
	  							  if (o == 1){
	  								  state = 0;
	  							  }
	  						  }
	  					  }
	  					  if(derecha2 == 2){
	  						  i = comparacion(movey,movey+l-mm,movey2+4);
	  						  if(i == 1){
	  							  o = comparacion(movex2+l,xx2[n3],movex);
	  							  if(o == 1){
	  								  state = 0;
	  							  }
	  							  o = comparacion(movex2+l,xx2[n3],movex+g);
	  							  if(o == 1){
	  								  state = 0;
	  							  }
	  						  }
	  					  }


	  					  c = 0;
	  				  }
	  				  //MOVIMIENTO DEL JUGADOR
	  				  movey -= vj1;
	  				  //RASTRO
	  				  FillRect(movex,movey+l,2,vj1,0x0000);
	  				  FillRect(movex+2,movey+l,2,vj1,rastroj1);
	  				  FillRect(movex+4,movey+l,1,vj1,0xFFFF);

	  				  FillRect(movex+5,movey+l,2,vj1,rastroj1);
	  				  FillRect(movex+7,movey+l,2,vj1,0x0000);

	  			  }
	  	  ///////////////////////////////////////////////////////////////////////////////////////////////////
	  			  if (abajo == 2){
	  				  FillRect(movex,movey,x,y,colorj1);//jugador 1(azul)
	  				  LCD_Bitmap(movex,movey+pr+1,9,18,moto_abajo);
	  				  int8_t oi = 0;
	  				  oi = d_posicion3(yy, n2, movey+l,movey+l+vj1);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = xi[oi];
	  					  f = xf[oi];
	  					  oi = comparacion(i,f,movex);
	  					  iio = comparacion(i,f,movex+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 0;
	  					  }
	  				  }
	  				  oi = d_posicion3(yy2, n4, movey+l,movey+l+vj1);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = xi2[oi];
	  					  f = xf2[oi];
	  					  oi = comparacion(i,f,movex);
	  					  iio = comparacion(i,f,movex+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 0;
	  					  }
	  				  }


	  				  if(derecha2 == 2){
	  					  io = comparacion(movex2+l+vj2,movex2+l,movex+4);
	  					  if(io == 1){
	  						  io = comparacion(movey+l, yy[n2], movey2);
	  						  if(io == 1){
	  							  state = 5;
	  							  //FillRect(movex+4,movey2,0xFE20);
	  						  }
	  						  io = comparacion(movey+l, yy[n2], movey2+g);
	  						  if(io == 1){
	  							  state = 5;
	  							  //FillRect(movex+4,movey2,0xFE20);
	  						  }
	  					  }
	  				  }
	  				  if(izquierda2 == 2){
	  					  io = comparacion(movex2,movex2-vj2,movex+4);
	  					  if(io == 1){
	  						  io = comparacion(movey+l,yy[n2],movey2);
	  						  if(io == 1){
	  							  state = 5;
	  						  }
	  						  io = comparacion(movey+l,yy[n2],movey2+g);
	  						  if(io == 1){
	  							  state = 5;
	  						  }
	  					  }
	  				  }
	  				  //CUANDO EL JUGADOR CRUZA
	  				  if(c == 1){
	  					  int8_t i;
	  					  uint8_t o;
	  					  i = d_posicion3(yy,n2,movey+mm,movey+l);
	  					  if(i != -1){
	  						  o = comparacion(xf[i], xi[i], movex);
	  						  if (o == 1){
	  							  state = 0;
	  						  }
	  						  o = comparacion(xf[i], xi[i], movex+g);
	  						  if(o==1){
	  							  state = 0;
	  						  }
	  					  }
	  					  i = d_posicion3(yy2,n4,movey+mm,movey+l);
	  					  if(i != -1){
	  						  o = comparacion(xf2[i], xi2[i], movex);
	  						  if (o == 1){
	  							  state = 0;
	  						  }
	  						  o = comparacion(xf2[i], xi2[i], movex+g);
	  						  if(o==1){
	  							  state = 0;
	  						  }
	  					  }
	  					  if(derecha2 == 2){
	  						  i = comparacion(movey+mm,movey+l,movey2+4);
	  						  if(i == 1){
	  							  o = comparacion(movex2+l,xx2[n3],movex);
	  							  if (o == 1){
	  								  state = 0;
	  							  }
	  							  o = comparacion(movex2+l,xx2[n3],movex+g);
	  							  if (o == 1){
	  								  state = 0;
	  							  }
	  						  }
	  					  }
	  					  if(izquierda2 == 2){
	  						  i = comparacion(movey+mm,movey+l,movey2+4);
	  						  if(i == 1){
	  							  o = comparacion(movex2,xx2[n3],movex);
	  							  if (o == 1){
	  								  state = 1;
	  							  }
	  							  o = comparacion(movex2,xx2[n3],movex+g);
	  							  if (o == 1){
	  								  state = 1;
	  							  }
	  						  }
	  					  }
	  					  c = 0;
	  				  }
	  				  movey += vj1;
	  				  //linea+=4;
	  				  //V_line(originx,originy,linea,0xFFFF);
	  				  FillRect(movex,movey-vj1,2,vj1,0x0000);
	  				  FillRect(movex+2,movey-vj1,2,vj1,rastroj1);
	  				  FillRect(movex+4,movey-vj1,1,vj1,0xFFFF);
	  				  FillRect(movex+5,movey-vj1,2,vj1,rastroj1);
	  				  FillRect(movex+7,movey-vj1,2,vj1,0x0000);
	  			  }
	  	  //////////////////////////////////////////////////////////////////////////////////////////////////////
	  			  if (derecha == 2){
	  				  FillRect(movex,movey,x,y,colorj1);//jugador 1(azul)
	  				  LCD_Bitmap(movex+pr+1,movey,18,9,moto_derecha);
	  				  int8_t oi = 0;
	  				  oi = d_posicion3(xx, n1, movex+l,movex+l+vj1);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = yi[oi];
	  					  f = yf[oi];
	  					  oi = comparacion(i,f,movey);
	  					  iio = comparacion(i,f,movey+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 0;
	  					  }
	  				  }
	  				  oi = d_posicion3(xx2, n3, movex+l,movex+l+vj1);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = yi2[oi];
	  					  f = yf2[oi];
	  					  oi = comparacion(i,f,movey);
	  					  iio = comparacion(i,f,movey+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 0;
	  					  }
	  				  }


	  				  //COLISION JUGADOR QUE SE MUEVE
	  				  if(arriba2 == 2){
	  					  io = comparacion(movey2,movey2-vj2,movey+4);
	  					  if(io == 1){
	  						  io = comparacion(movex+l,xx[n1],movex2);
	  						  if(io == 1){
	  							  state = 5;
	  						  }
	  						  io = comparacion(movex+l,xx[n1],movex2+g);
	  						  if(io == 1){
	  							  state = 5;
	  						  }
	  					  }
	  				  }
	  				  if(abajo2 == 2){
	  					  io = comparacion(movey2+l,movey2+l+vj2,movey+4);
	  					  if(io == 1){
	  						  io = comparacion(movex+l,xx[n1],movex2);
	  						  if(io == 1){
	  							  state = 5;
	  						  }
	  						  io = comparacion(movex+l,xx[n1],movex2+g);
	  						  if(io == 1){
	  							  state = 5;
	  						  }
	  					  }
	  				  }
	  				  if(c == 1){
	  					  int8_t i=0;
	  					  uint8_t o=0;
	  					  i = d_posicion3(xx,n1,movex+mm,movex+l);
	  					  if(i != -1){
	  						  o = comparacion(yf[i], yi[i], movey);
	  						  if (o == 1){
	  							  state = 0;
	  						  }
	  						  o = comparacion(yf[i], yi[i], movey+g);
	  						  if(o==1){
	  							  state = 0;
	  						  }
	  					  }
	  					  i = d_posicion3(xx2,n3,movex+mm,movex+l);
	  					  if(i != -1){
	  						  o = comparacion(yf2[i], yi2[i], movey);
	  						  if (o == 1){
	  							  state = 0;
	  						  }
	  						  o = comparacion(yf2[i], yi2[i], movey+g);
	  						  if(o==1){
	  							  state = 0;
	  						  }
	  					  }
	  					  if(arriba2 == 2){
	  						  i = comparacion(movex+mm,movex+l,movex2+4);
	  						  if(i == 1){
	  							  o = comparacion(movey2,yy2[n4],movey);
	  							  if(o == 1){
	  								  state = 0;
	  							  }
	  							  o = comparacion(movey2,yy2[n4],movey+g);
	  							  if(o == 1){
	  								  state = 0;
	  							  }
	  						  }
	  					  }
	  					  if(abajo2 == 2){
	  						  i = comparacion(movex+mm,movex+l,movex2+4);
	  						  if(i == 1){
	  							  o = comparacion(movey2+l,yy2[n4],movey);
	  							  if(o == 1){
	  								  state = 0;
	  							  }
	  							  o = comparacion(movey2+l,yy2[n4],movey+g);
	  							  if(o == 1){
	  								  state = 0;
	  							  }
	  						  }
	  					  }
	  					  c = 0;
	  				  }
	  				  movex += vj1;
	  				  //H_line(originx,originy,linea,0xFFFF);
	  				  FillRect(movex-vj1,movey,vj1,2,0x0000);
	  				  FillRect(movex-vj1,movey+2,vj1,2,rastroj1);
	  				  FillRect(movex-vj1,movey+4,vj1,1,0xFFFF);
	  				  FillRect(movex-vj1,movey+5,vj1,2,rastroj1);
	  				  FillRect(movex-vj1,movey+7,vj1,2,0x0000);
	  			  }
	  	  ////////////////////////////////////////////////////////////////////////////////////////////////////
	  			  if (izquierda == 2){
	  				  FillRect(movex,movey,x,y,colorj1);//jugador 1(azul)
	  				  LCD_Bitmap(movex+pr,movey,18,9,moto_izquierda);
	  				  int8_t oi = 0;
	  				  oi = d_posicion3(xx, n1, movex,movex-vj1);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = yi[oi];
	  					  f = yf[oi];
	  					  oi = comparacion(i,f,movey);
	  					  iio = comparacion(i,f,movey+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 0;
	  					  }
	  				  }
	  				  oi = d_posicion3(xx2, n3, movex,movex-vj1);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = yi2[oi];
	  					  f = yf2[oi];
	  					  oi = comparacion(i,f,movey);
	  					  iio = comparacion(i,f,movey+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 0;
	  					  }
	  				  }
	  				  //COLISION JUGADOR QUE SE MUEVE
	  				  if(arriba2 == 2){
	  					  io = comparacion(movey2,movey2+vj2,movey+4);
	  						  if(io == 1){
	  							  io = comparacion(movex,xx[n1],movex2);
	  							  if(io == 1){
	  								  state = 5;
	  							  }
	  							  io = comparacion(movex,xx[n1],movex2+g);
	  							  if(io == 1){
	  								  state = 5;
	  							  }
	  						  }
	  					  }

	  				  if(abajo2 == 2){
	  					  io = comparacion(movey2+l,movey2+l+vj2,movey+4);
	  						  if(io == 1){
	  							  io = comparacion(movex,xx[n1],movex2);
	  							  if(io == 1){
	  								  state = 5;
	  							  }
	  							  io = comparacion(movex,xx[n1],movex2+g);
	  							  if(io == 1){
	  								  state = 5;
	  							  }
	  						  }
	  					  }
	  				  if(c == 1){
	  					  int8_t i=0;
	  					  uint8_t o=0;
	  					  i = d_posicion3(xx,n1,movex,movex+l-mm);
	  					  if(i != -1){
	  						  o = comparacion(yf[i], yi[i], movey);
	  						  if (o == 1){
	  							  state = 0;
	  						  }
	  						  o = comparacion(yf[i], yi[i], movey+g);
	  						  if(o==1){
	  							  state = 0;
	  						  }
	  					  }
	  					  i = d_posicion3(xx2,n3,movex,movex+l-mm);
	  					  if(i != -1){
	  						  o = comparacion(yf2[i], yi2[i], movey);
	  						  if (o == 1){
	  							  state = 0;
	  						  }
	  						  o = comparacion(yf2[i], yi2[i], movey+g);
	  						  if(o==1){
	  							  state = 0;
	  						  }
	  					  }
	  					  if(arriba2 == 2){
	  						  i = comparacion(movex,movex+l-mm,movex2+4);
	  						  if(i == 1){
	  							  o = comparacion(movey2,yy2[n4],movey);
	  							  if(o == 1){
	  								  state = 0;
	  							  }
	  							  o = comparacion(movey2,yy2[n4],movey+g);
	  							  if(o == 1){
	  								  state = 0;
	  							  }
	  						  }
	  					  }
	  					  if(abajo2 == 2){
	  						  i = comparacion(movex,movex+l-mm,movex2+4);
	  						  if(i == 1){
	  							  o = comparacion(movey2+l,yy2[n4],movey);
	  							  if(o == 1){
	  								  state = 0;
	  							  }
	  							  o = comparacion(movey2+l,yy2[n4],movey+g);
	  							  if(o == 1){
	  								  state = 0;
	  							  }
	  						  }
	  					  }
	  					  c = 0;
	  				  }
	  				  movex -= vj1;
	  				  //linea+=4;
	  				  //H_line(movex+l,originy,linea,0xFFFF);
	  				  FillRect(movex+l,movey,vj1,2,0x0000);
	  				  FillRect(movex+l,movey+2,vj1,2,rastroj1);
	  				  FillRect(movex+l,movey+4,vj1,1,0xFFFF);
	  				  FillRect(movex+l,movey+5,vj1,2,rastroj1);
	  				  FillRect(movex+l,movey+7,vj1,2,0x0000);

	  			  }
	  			  //******************************************************************************
	  			  //******************************JUGADOR 2***************************************
	  			  //*******************************************************************************
	  			  if (arriba2 == 2){
	  				  FillRect(movex2,movey2,x2,y2,colorj2);//jugador 2 (amarillo)
	  				  LCD_Bitmap(movex2,movey2+pr+1,9,18,moto_arriba);
	  				  int8_t oi = 0;
	  				  oi = d_posicion3(yy, n2, movey2,movey2-vj2);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = xi[oi];
	  					  f = xf[oi];
	  					  oi = comparacion(i,f,movex2);
	  					  iio = comparacion(i,f,movex2+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 5;
	  					  }
	  				  }
	  				  oi = d_posicion3(yy2, n4, movey2,movey2-vj2);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = xi2[oi];
	  					  f = xf2[oi];
	  					  oi = comparacion(i,f,movex2);
	  					  iio = comparacion(i,f,movex2+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 5;
	  					  }
	  				  }

	  				  //COLISION CUANDO EL JUGADOR SE MUEVE
	  				  if(izquierda == 2){
	  					  io = comparacion(movex,movex-(vj1),movex2+4);
	  					  if(io == 1){
	  						  io = comparacion(movey2, yy2[n4], movey);
	  						  if(io == 1){
	  							  state = 0;
	  							  //FillRect(movex+4,movey2,0xFE20);
	  						  }

	  						  io = comparacion(movey2, yy2[n4], movey+g);
	  						  if(io == 1){
	  							  state = 0;
	  						  }
	  					  }
	  				  }
	  				  if(derecha == 2){
	  					  io = comparacion(movex+l+vj1,movex+l,movex2+4);
	  					  if(io == 1){
	  						  io = comparacion(movey2, yy2[n4], movey);
	  						  if(io == 1){
	  							  state = 0;
	  						  }
	  						  io = comparacion(movey2,yy2[n4],movey+g);
	  						  if(io == 1){
	  							  state = 0;
	  						  }
	  					  }

	  				  }
	  				  if(c == 1){
	  					  int8_t i=0;
	  					  uint8_t o=0;
	  					  i = d_posicion3(yy,n2,movey2+l-mm,movey2);
	  					  if(i != -1){
	  						  o = comparacion(xf[i], xi[i], movex2);
	  						  if (o == 1){
	  							  state = 5;
	  						  }
	  						  o = comparacion(xf[i], xi[i], movex2+g);
	  						  if(o==1){
	  							  state = 5;
	  						  }
	  					  }
	  					  i = d_posicion3(yy2,n4,movey2+l-mm,movey2);
	  					  if(i != -1){
	  						  o = comparacion(xf2[i], xi2[i], movex2);
	  						  if (o == 1){
	  							  state = 5;
	  						  }
	  						  o = comparacion(xf2[i], xi2[i], movex2+g);
	  						  if(o==1){
	  							  state = 5;
	  						  }
	  					  }
	  					  if(izquierda == 2){
	  						  i = comparacion(movey2,movey2+l-mm,movey+4);
	  						  if(i == 1){
	  							  o = comparacion(movex,xx[n1],movex2);
	  							  if (o == 1){
	  								  state = 5;
	  							  }
	  							  o = comparacion(movex,xx[n1],movex2+g);
	  							  if (o == 1){
	  								  state = 5;
	  							  }
	  						  }
	  					  }
	  					  if(derecha == 2){
	  						  i = comparacion(movey2,movey2+l-mm,movey+4);
	  						  if(i == 1){
	  							  o = comparacion(movex+l,xx[n1],movex2);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  							  o = comparacion(movex+l,xx[n1],movex2+g);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  						  }
	  					  }
	  					  c = 0;
	  				  }
	  				  movey2 -= vj2;
	  				  //linea2+=4;
	  				  //V_line(originx2,movey2+l,linea2,0xFFFF);
	  				  FillRect(movex2,movey2+l,2,vj2,0x0000);
	  				  FillRect(movex2+2,movey2+l,2,vj2,rastroj2);
	  				  FillRect(movex2+4,movey2+l,1,vj2,0xFFFF);
	  				  FillRect(movex2+5,movey2+l,2,vj2,rastroj2);
	  				  FillRect(movex2+7,movey2+l,2,vj2,0x0000);
	  				  if (c == 1){

	  					  c = 0;
	  				  }
	  			  }
	  	  //////////////////////////////////////////////////////////////////////////////////////////////////////
	  			  if (abajo2 == 2){
	  				  FillRect(movex2,movey2,x2,y2,colorj2);//jugador 2 (amarillo)
	  				  LCD_Bitmap(movex2,movey2+pr,9,18,moto_abajo);
	  				  int8_t oi = 0;
	  				  oi = d_posicion3(yy, n2, movey2+l,movey2+l+vj2);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = xi[oi];
	  					  f = xf[oi];
	  					  oi = comparacion(i,f,movex2);
	  					  iio = comparacion(i,f,movex2+g);
	  					  if(oi == 1 || iio == 1){

	  						  state = 5;
	  					  }
	  				  }
	  				  oi = d_posicion3(yy2, n4, movey2+l,movey2+l+vj2);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = xi2[oi];
	  					  f = xf2[oi];
	  					  oi = comparacion(i,f,movex2);
	  					  iio = comparacion(i,f,movex2+g);
	  					  if(oi == 1 || iio == 1){

	  						  state = 5;
	  					  }
	  				  }

	  				  if(derecha == 2){
	  					  io = comparacion(movex+l+vj1,movex+l,movex2+4);
	  					  if(io == 1){
	  						  io = comparacion(movey2+l, yy2[n4], movey);
	  						  if(io == 1){
	  							  state = 0;
	  							  //FillRect(movex+4,movey2,0xFE20);
	  						  }
	  						  io = comparacion(movey2+l, yy2[n4], movey+g);
	  						  if(io == 1){
	  							  state = 0;
	  							  //FillRect(movex+4,movey2,0xFE20);
	  						  }
	  					  }
	  				  }
	  				  if(izquierda == 2){
	  					  io = comparacion(movex,movex-vj1,movex2+4);
	  					  if(io == 1){
	  						  io = comparacion(movey2+l,yy2[n4],movey);
	  						  if(io == 1){
	  							  state = 0;
	  						  }
	  						  io = comparacion(movey2+l,yy2[n4],movey+g);
	  						  if(io == 1){
	  							  state = 0;
	  						  }
	  					  }
	  				  }
	  				  movey2 += vj2;
	  				  if(c == 1){
	  					  int8_t i;
	  					  uint8_t o;
	  					  i = d_posicion3(yy,n2,movey2+mm,movey2+l);
	  					  if(i != -1){
	  						  o = comparacion(xf[i], xi[i], movex2);
	  						  if (o == 1){
	  							  state = 5;
	  						  }
	  						  o = comparacion(xf[i], xi[i], movex2+g);
	  						  if(o==1){
	  							  state = 5;
	  						  }
	  					  }
	  					  i = d_posicion3(yy2,n4,movey2+mm,movey2+l);
	  					  if(i != -1){
	  						  o = comparacion(xf2[i], xi2[i], movex2);
	  						  if (o == 1){
	  							  state = 5;
	  						  }
	  						  o = comparacion(xf2[i], xi2[i], movex2+g);
	  						  if(o==1){
	  							  state = 5;
	  						  }
	  					  }
	  					  if(izquierda == 2){
	  						  i = comparacion(movey2+mm,movey2+l,movey+4);
	  						  if(i == 1){
	  							  o = comparacion(movex,xx[n1],movex2);
	  							  if (o == 1){
	  								  state = 5;
	  							  }
	  							  o = comparacion(movex,xx[n1],movex2+g);
	  							  if (o == 1){
	  								  state = 5;
	  							  }
	  						  }
	  					  }
	  					  if(derecha == 2){
	  						  i = comparacion(movey2+mm,movey2+l,movey+4);
	  						  if(i == 1){
	  							  o = comparacion(movex+l,xx[n1],movex2);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  							  o = comparacion(movex+l,xx[n1],movex2+g);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  						  }
	  					  }
	  					  c = 0;
	  				  }
	  				  //linea2+=4;
	  				  //V_line(originx2,originy2,linea2,0xFFFF);
	  				  FillRect(movex2,movey2-vj2,2,vj2,0x0000);
	  				  FillRect(movex2+2,movey2-vj2,2,vj2,rastroj2);
	  				  FillRect(movex2+4,movey2-vj2,1,vj2,0xFFFF);
	  				  FillRect(movex2+5,movey2-vj2,2,vj2,rastroj2);
	  				  FillRect(movex2+7,movey2-vj2,2,vj2,0x0000);
	  			  }
	  	  /////////////////////////////////////////////////////////////////////////////////////////////////////
	  			  if (derecha2 == 2){
	  				  FillRect(movex2,movey2,x2,y2,colorj2);//jugador 2 (amarillo)
	  				  LCD_Bitmap(movex2+pr+1,movey2,18,9,moto_derecha);
	  				  int8_t oi = 0;
	  				  oi = d_posicion3(xx, n1, movex2+l,movex2+l+vj2);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = yi[oi];
	  					  f = yf[oi];
	  					  oi = comparacion(i,f,movey2);
	  					  iio = comparacion(i,f,movey2+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 5;
	  					  }
	  				  }
	  				  oi = d_posicion3(xx2, n3, movex2+l,movex2+l+vj2);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = yi2[oi];
	  					  f = yf2[oi];
	  					  oi = comparacion(i,f,movey2);
	  					  iio = comparacion(i,f,movey2+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 5;
	  					  }
	  				  }

	  				  //COLISION JUGADOR QUE SE MUEVE
	  				  if(arriba == 2){
	  					  io = comparacion(movey,movey-vj1,movey2+4);
	  					  if(io == 1){
	  						  io = comparacion(movex2+l,xx2[n3],movex);
	  						  if(io == 1){
	  							  state = 0;
	  						  }
	  						  io = comparacion(movex2+l,xx2[n3],movex+g);
	  						  if(io == 1){
	  							  state = 0;
	  						  }
	  					  }
	  				  }
	  				  if(abajo == 2){
	  					  io = comparacion(movey+l,movey+l+vj1+1,movey2+4);
	  					  if(io == 1){
	  						  io = comparacion(movex2+l,xx2[n3],movex);
	  						  if(io == 1){
	  							  state = 0;
	  						  }
	  						  io = comparacion(movex2+l,xx2[n3],movex+g);
	  						  if(io == 1){
	  							  state = 0;
	  						  }
	  					  }
	  				  }
	  				  if(c == 1){
	  					  int8_t i=0;
	  					  uint8_t o=0;
	  					  i = d_posicion3(xx,n1,movex2+mm,movex2+l);
	  					  if(i != -1){
	  						  o = comparacion(yf[i], yi[i], movey2);
	  						  if (o == 1){
	  							  state = 5;
	  						  }
	  						  o = comparacion(yf[i], yi[i], movey2+g);
	  						  if(o==1){
	  							  state = 5;
	  						  }
	  					  }
	  					  i = d_posicion3(xx2,n3,movex2+mm,movex2+l);
	  					  if(i != -1){
	  						  o = comparacion(yf2[i], yi2[i], movey2);
	  						  if (o == 1){
	  							  state = 5;
	  						  }
	  						  o = comparacion(yf2[i], yi2[i], movey2+g);
	  						  if(o==1){
	  							  state = 5;
	  						  }
	  					  }
	  					  if(arriba == 2){
	  						  i = comparacion(movex2+mm,movex2+l,movex+4);
	  						  if(i == 1){
	  							  o = comparacion(movey,yy[n2],movey2);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  							  o = comparacion(movey,yy[n2],movey2+g);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  						  }
	  					  }
	  					  if(abajo == 2){
	  						  i = comparacion(movex2+mm,movex2+l,movex+4);
	  						  if(i == 1){
	  							  o = comparacion(movey+l,yy[n2],movey2);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  							  o = comparacion(movey+l,yy[n2],movey2+g);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  						  }
	  					  }
	  					  c = 0;
	  				  }
	  				  movex2 += vj2;
	  				  //linea2+=4;
	  				  //H_line(originx2,originy2,linea2,0xFFFF);
	  				  FillRect(movex2-vj2,movey2,vj2,2,0x0000);
	  				  FillRect(movex2-vj2,movey2+2,vj2,2,rastroj2);
	  				  FillRect(movex2-vj2,movey2+4,vj2,1,0xFFFF);
	  				  FillRect(movex2-vj2,movey2+5,vj2,2,rastroj2);
	  				  FillRect(movex2-vj2,movey2+7,vj2,2,0x0000);
	  			  }
	  	  ///////////////////////////////////////////////////////////////////////////////////////////////////
	  			  if (izquierda2 == 2){
	  				  FillRect(movex2,movey2,x2,y2,colorj2);//jugador 2 (amarillo)
	  				  LCD_Bitmap(movex2+pr,movey2,18,9,moto_izquierda);
	  				  int8_t oi = 0;
	  				  oi = d_posicion3(xx, n1, movex2,movex2-vj2);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = yi[oi];
	  					  f = yf[oi];
	  					  oi = comparacion(i,f,movey2);
	  					  iio = comparacion(i,f,movey2+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 5;
	  					  }
	  				  }
	  				  oi = d_posicion3(xx2, n3, movex2,movex2+vj2);
	  				  if (oi != -1){
	  					  //FillRect(288,0,32,300,0xF800);
	  					  //HAL_Delay(100);
	  					  //illRect(288,0,32,300,0x630C);
	  					  uint8_t i;
	  					  uint8_t f;
	  					  uint8_t iio;

	  					  i = yi2[oi];
	  					  f = yf2[oi];
	  					  oi = comparacion(i,f,movey2);
	  					  iio = comparacion(i,f,movey2+g);
	  					  if(oi == 1 || iio == 1){
	  						  state = 5;
	  					  }
	  				  }

	  				  //COLISION JUGADOR QUE SE MUEVE
	  				  if(arriba == 2){
	  					  io = comparacion(movey,movey+vj1,movey2+4);
	  						  if(io == 1){
	  							  io = comparacion(movex2,xx2[n3],movex);
	  							  if(io == 1){
	  								  state = 0;
	  							  }
	  							  io = comparacion(movex2,xx2[n3],movex+g);
	  							  if(io == 1){
	  								  state = 0;
	  							  }
	  						  }
	  					  }

	  				  if(abajo == 2){
	  					  io = comparacion(movey+l,movey+l+vj1,movey2+4);
	  						  if(io == 1){
	  							  io = comparacion(movex2,xx2[n3],movex);
	  							  if(io == 1){
	  								  state = 0;
	  							  }
	  							  io = comparacion(movex2,xx2[n3],movex+g);
	  							  if(io == 1){
	  								  state = 0;
	  							  }
	  						  }
	  					  }
	  				  if(c == 1){
	  					  int8_t i=0;
	  					  uint8_t o=0;
	  					  i = d_posicion3(xx,n1,movex2,movex2+l-mm);
	  					  if(i != -1){
	  						  o = comparacion(yf[i], yi[i], movey);
	  						  if (o == 1){
	  							  state = 5;
	  						  }
	  						  o = comparacion(yf[i], yi[i], movey+g);
	  						  if(o==1){
	  							  state = 5;
	  						  }
	  					  }
	  					  i = d_posicion3(xx2,n3,movex2,movex2+l-mm);
	  					  if(i != -1){
	  						  o = comparacion(yf2[i], yi2[i], movey);
	  						  if (o == 1){
	  							  state = 5;
	  						  }
	  						  o = comparacion(yf2[i], yi2[i], movey+g);
	  						  if(o==1){
	  							  state = 5;
	  						  }
	  					  }
	  					  if(arriba == 2){
	  						  i = comparacion(movex2,movex2+l-mm,movex+4);
	  						  if(i == 1){
	  							  o = comparacion(movey,yy[n2],movey2);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  							  o = comparacion(movey,yy[n2],movey2+g);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  						  }
	  					  }
	  					  if(abajo == 2){
	  						  i = comparacion(movex2,movex2+l-mm,movex+4);
	  						  if(i == 1){
	  							  o = comparacion(movey+l,yy[n2],movey2);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  							  o = comparacion(movey+l,yy[n2],movey2+g);
	  							  if(o == 1){
	  								  state = 5;
	  							  }
	  						  }
	  					  }
	  					  c = 0;
	  				  }
	  				  movex2 -= vj2;
	  				  //linea2+=4;
	  				  //H_line(movex2+l,originy2,linea2,0xFFFF);
	  				  FillRect(movex2+l,movey2,vj2,2,0x0000);
	  				  FillRect(movex2+l,movey2+2,vj2,2,rastroj2);
	  				  FillRect(movex2+l,movey2+4,vj2,1,0xFFFF);
	  				  FillRect(movex2+l,movey2+5,vj2,2,rastroj2);
	  				  FillRect(movex2+l,movey2+7,vj2,2,0x0000);

	  			  }
	  		  }while(state == 3);
	  	  }else if(state == 5){
	  		  char buffer[4];
	  		  transmit_uart("3");
	  		  FillRect(movex,movey,x,y,colorj1);//jugador 1(azul)0x1112
	  		  FillRect(movex2,movey2,x2,y2,colorj2);//jugador 2 (amarillo)0xFE20
	  		  if(derecha == 2){
				  LCD_Bitmap(movex+pr,movey,18,9,moto_derecha);

			  }
			  if(izquierda == 2){
				  LCD_Bitmap(movex+pr,movey,18,9,moto_izquierda);

			  }
			  if(abajo == 2){
				  LCD_Bitmap(movex,movey+pr,9,18,moto_abajo);

			  }
			  if(arriba == 2){
				  LCD_Bitmap(movex,movey+pr,9,18,moto_arriba);

			  }
	  		  if(derecha2 == 2){
	  			  LCD_Bitmap(movex2+pr,movey2,18,9,moto_derecha);
	  			  LCD_Sprite(movex2+20,movey2-4,20,16,explosion,5,0,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2+20,movey2-4,20,16,explosion,5,1,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2+20,movey2-4,20,16,explosion,5,2,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2+20,movey2-4,20,16,explosion,5,3,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2+20,movey2-4,20,16,explosion,5,4,0,0);
				  HAL_Delay(150);
	  		  }
	  		  if(izquierda2 == 2){
	  			  LCD_Bitmap(movex2+pr,movey2,18,9,moto_izquierda);
	  			  LCD_Sprite(movex2-8,movey2-4,20,16,explosion,5,0,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-8,movey2-4,20,16,explosion,5,1,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-8,movey2-4,20,16,explosion,5,2,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-8,movey2-4,20,16,explosion,5,3,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-8,movey2-4,20,16,explosion,5,4,0,0);
				  HAL_Delay(150);
	  		  }
	  		  if(abajo2 == 2){
	  			  LCD_Bitmap(movex2,movey2+pr,9,18,moto_abajo);
	  			  LCD_Sprite(movex2-6,movey2+20,20,16,explosion,5,0,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-6,movey2+20,20,16,explosion,5,1,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-6,movey2+20,20,16,explosion,5,2,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-6,movey2+20,20,16,explosion,5,3,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-6,movey2+20,20,16,explosion,5,4,0,0);
				  HAL_Delay(150);
	  		  }
	  		  if(arriba2 == 2){
	  			  LCD_Bitmap(movex2,movey2+pr,9,18,moto_arriba);
	  			  LCD_Sprite(movex2-6,movey2-8,20,16,explosion,5,0,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-6,movey2-8,20,16,explosion,5,1,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-6,movey2-8,20,16,explosion,5,2,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-6,movey2-8,20,16,explosion,5,3,0,0);
				  HAL_Delay(150);
				  LCD_Sprite(movex2-6,movey2-8,20,16,explosion,5,4,0,0);
				  HAL_Delay(150);
	  		  }

	  		  HAL_Delay(2000);
	  		  LCD_Clear(0x0000);
	  		  LCD_Print("Fin Del Juego",50,90,2,0xFFFF,0x0000);
	  		  LCD_Print("Jugador 1 gana", 40,110,2,rastroj1,0x0000);
	  		  gj1++;
	  		  itoa(gj1,buffer,10);
	  		  LCD_Print(buffer, 145,130,2,rastroj1,0x0000);
	  		  LCD_Print("-", 160,130,2,0xFFFF,0x0000);
	  		  itoa(gj2, buffer,10);
	  		  if(gj2 == 0){
	  			  LCD_Print("0",175,130,2,rastroj2,0x0000);
	  		  }else{
	  			  LCD_Print(buffer,175,130,2,rastroj2,0x0000);
	  		  }

	  		  do{
	  			  HAL_Delay(50);
	  		  }while(state == 5);
	  	  }else if(state == 6){//menu
	  		  LCD_Clear(0x00);
	  		  V_line(0,0,240,0x212E);
	  		  V_line(32,0,240,0x212E);
			  V_line(64,0,240,0x212E);
			  V_line(96,0,240,0x212E);
			  V_line(128,0,240,0x212E);
			  V_line(160,0,240,0x212E);
			  V_line(192,0,240,0x212E);
			  V_line(224,0,240,0x212E);
			  V_line(256,0,240,0x212E);
			  V_line(288,0,240,0x212E);
			  V_line(320,0,240,0x212E);
			  H_line(0,0,320,0x212E);
			  H_line(0,32,320,0x212E);
			  H_line(0,64,320,0x212E);
			  H_line(0,96,320,0x212E);
			  H_line(0,128,320,0x212E);
			  H_line(0,160,320,0x212E);
			  H_line(0,192,320,0x212E);
			  H_line(0,224,320,0x212E);
			  H_line(0,240,320,0x212E);

	  		  transmit_uart("1");
	  		  gj1 = 0;
	  		  gj2 = 0;
	  		  cd1 = 0;
	  		  cd2 = 0;
	  		  HAL_TIM_Base_Stop_IT(&htim14);
	  		  HAL_TIM_Base_Stop_IT(&htim13);

	  		  //LCD_Bitmap(0,0,320,180,menu2);
	  		 // FillRect(85,60,140,50,0xFFFF);//logo
	  		  LCD_Bitmap(60,40,190,49,logo);
	  		  //FillRect(0,120,230,40,0xFFFF);//moto
	  		  LCD_Bitmap(0,135,230,42,moto_);
	  		  //LCD_Clear(0x0000);
	  		  //LCD_Print("Menu lol",50,90,2,0xFFFF,0x0000);
	  		  while(state == 6){//menu
	  			  LCD_Print("Presiona cualquier boton",60,195,1,azul,0x0000);
	  			  HAL_Delay(500);
	  			  LCD_Print("Presiona cualquier boton",60,195,1,0x0000,0x0000);
	  			  //FillRect(60,195,200,12,0x0000);
	  			  HAL_Delay(500);
	  		  }
	  	  }else if(state == 7){
	  		  LCD_Clear(0x0000);
	  		  FillRect(65,60,50,50,azul);
	  		  FillRect(135,60,50,50,verde);
	  		  FillRect(205,60,50,50,naranja);
	  		  FillRect(65,130,50,50,amarillo);
	  		  FillRect(135,130,50,50,rojo);
	  		  FillRect(205,130,50,50,rosa);
	  		  j1[1] = 1;
	  		  j2[1] = 4;
	  		  j1[2] = 0;
	  		  j2[2] = 0;
	  		  do{
	  			  if(j1[2] == 0){
	  				  if(j1[1] == 1){
	  					  LCD_Print("J1",75,70,2,0xFFFF,azul);
	  					  j1borrar();
	  				  }else if(j1[1] == 2){
	  					  LCD_Print("J1",145,70,2,0xFFFF,verde);
	  					  j1borrar();
	  				  }else if(j1[1] == 3){
	  					  LCD_Print("J1",215,70,2,0xFFFF,naranja);
	  					  j1borrar();
	  				  }else if(j1[1] == 4){
	  					  LCD_Print("J1",75,140,2,0xFFFF,amarillo);
	  					  j1borrar();
	  				  }else if(j1[1] == 5){
	  					  LCD_Print("J1",145,140,2,0xFFFF,rojo);
	  					  j1borrar();
	  				  }else if(j1[1] == 6){
	  					  LCD_Print("J1",215,140,2,0xFFFF,rosa);
	  					  j1borrar();
	  				  }
	  			  }else if(j1[2] == 1){
	  				  LCD_Print("J1 Listo",75,190,1,0xFFFF,0x0000);
	  			  }
	  			  if(j2[2] == 0){
	  				  if(j2[1] == 1){
	  					  LCD_Print("J2",75,70,2,0xFFFF,azul);
	  					  j2borrar();
	  				  }else if(j2[1] == 2){
	  					  LCD_Print("J2",145,70,2,0xFFFF,verde);
	  					  j2borrar();
	  				  }else if(j2[1] == 3){
	  					  LCD_Print("J2",215,70,2,0xFFFF,naranja);
	  					  j2borrar();
	  				  }else if(j2[1] == 4){
	  					  LCD_Print("J2",75,140,2,0xFFFF,amarillo);
	  					  j2borrar();
	  				  }else if(j2[1] == 5){
	  					  LCD_Print("J2",145,140,2,0xFFFF,rojo);
	  					  j2borrar();
	  				  }else if(j2[1] == 6){
	  					  LCD_Print("J2",215,140,2,0xFFFF,rosa);
	  					  j2borrar();
	  				  }
	  			  }else if(j2[2] == 1){
	  				  LCD_Print("J2 Listo",200,190,1,0xFFFF,0x0000);
	  			  }
	  			  if(j2[2] == 1 && j1[2] == 1){
	  				  state = 8;
	  			  }
	  		  }while(state == 7);
	  	  }else if(state == 8){
	  		  gj1 = 0;
	  		  gj2 = 0;
	  		  vaciar_listas();
	  		  movex = 0;
	  		  movey = 0;

	  		  movex2 = 0;
	  		  movey2 = 240-g;
	  		  x = l;
	  		  y = g;
	  		  x2 = l;
	  		  y2 = g;
	  		  FillRect(65,60,200,150,0x0000);
	  		  //FillRect(255,0,65,300,0x630C);
	  		  FillRect(255,0,2,240,azul);
	  		  FillRect(257,0,1,240,0xFFFF);
	  		  FillRect(258,0,2,240,azul);
	  		  V_line(32,0,240,0x212E);
	  		  V_line(64,0,240,0x212E);
	  		  V_line(96,0,240,0x212E);
	  		  V_line(128,0,240,0x212E);
	  		  V_line(160,0,240,0x212E);
	  		  V_line(192,0,240,0x212E);
	  		  V_line(224,0,240,0x212E);
			  H_line(0,32,255,0x212E);
			  H_line(0,64,255,0x212E);
			  H_line(0,96,255,0x212E);
			  H_line(0,128,255,0x212E);
			  H_line(0,160,255,0x212E);
			  H_line(0,192,255,0x212E);
			  H_line(0,224,255,0x212E);
	  		  arriba = 0;
	  		  abajo = 0;
	  		  derecha = 2;
	  		  izquierda = 0;
	  		  arriba2 = 0;
	  		  abajo2 = 0;
	  		  derecha2 = 2;
	  		  izquierda2 = 0;
	  		  HAL_Delay(100);

	  		  if(j1[1] == 1){
	  			  rastroj1 = azul;
	  			  colorj1 = azulo;
	  		  }else if(j1[1] == 2){
	  			  rastroj1 = verde;
	  			  colorj1 = verdeo;
	  		  }else if(j1[1] == 3){
	  			  rastroj1 = naranja;
	  			  colorj1 = naranjao;
	  		  }else if(j1[1] == 4){
	  			  rastroj1 = amarillo;
	  			  colorj1 = amarilloo;
	  		  }else if(j1[1] == 5){
	  			  rastroj1 = rojo;
	  			  colorj1 = rojoo;
	  		  }else if(j1[1] == 6){
	  			  rastroj1 = rosa;
	  			  colorj1 = rosao;
	  		  }
	  		  if(j2[1] == 1){
	  			  rastroj2 = azul;
	  			  colorj2 = azulo;
	  		  }else if(j2[1] == 2){
	  			  rastroj2 = verde;
	  			  colorj2 = verdeo;
	  		  }else if(j2[1] == 3){
	  			  rastroj2 = naranja;
	  			  colorj2 = naranjao;
	  		  }else if(j2[1] == 4){
	  			  rastroj2 = amarillo;
	  			  colorj2 = amarilloo;
	  		  }else if(j2[1] == 5){
	  			  rastroj2 = rojo;
	  			  colorj2 = rojoo;
	  		  }else if(j2[1] == 6){
	  			  rastroj2 = rosa;
	  			  colorj2 = rosao;
	  		  }
	  		  state = 3;
	  	  }else if(state == 9){//estado de pruebas de bitmaps
	  		  LCD_Clear(0x0000);

	  		  do{









	  		  }while(state == 9);
	  	  }





	  			  HAL_Delay(50);


	  	  }


	    }
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
  * @brief TIM13 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM13_Init(void)
{

  /* USER CODE BEGIN TIM13_Init 0 */

  /* USER CODE END TIM13_Init 0 */

  /* USER CODE BEGIN TIM13_Init 1 */

  /* USER CODE END TIM13_Init 1 */
  htim13.Instance = TIM13;
  htim13.Init.Prescaler = 1000-1;
  htim13.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim13.Init.Period = 16000-1;
  htim13.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim13.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM13_Init 2 */

  /* USER CODE END TIM13_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 1000-1;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 16000-1;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

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
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();

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
void transmit_uart(char *message) {
    HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);
}

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
int8_t d_posicion2(uint8_t arr[], uint8_t size, uint8_t numero, uint8_t velocidad){
	uint8_t i = 0;
	uint8_t lol;
	for(i = 0; i <= size; i++){
		lol = comparacion(arr[i],numero,numero+velocidad);
		if (lol ==1){
			return i;
		}
	}
	return -1;
}
int8_t d_posicion3(uint8_t arr[], uint8_t size, uint8_t numero, uint8_t numero2){
	uint8_t i = 0;
	uint8_t lol;
	for(i = 0; i <= size; i++){
		lol = comparacion(numero,numero2,arr[i]);
		if (lol ==1){
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
	for(int i = 0; i <= n3; i++){
		xx2[i] = 0;
		yi2[i] = 0;
		yf2[i] = 0;
	}
	for(int i = 0; i <= n4; i++){
		yy2[i] = 0;
		xi2[i] = 0;
		xf2[i] = 0;
	}
	n1 = 0;
	n2 = 0;
	n3 = 0;
	n4 = 0;

}
void j1borrar(void){
	if(j1[0] == 1){
		FillRect(65,60,50,50,azul);
	}else if(j1[0] == 2){

		FillRect(135,60,50,50,verde);

	}else if(j1[0] == 3){

		FillRect(205,60,50,50,naranja);

	}else if(j1[0] == 4){

	    FillRect(65,130,50,50,amarillo);

	}else if(j1[0] == 5){

	    FillRect(135,130,50,50,rojo);

	}else if(j1[0] == 6){

		FillRect(205,130,50,50,rosa);
	}

}
void j2borrar(void){
	if(j2[0] == 1){
		FillRect(65,60,50,50,azul);
	}else if(j2[0] == 2){

		FillRect(135,60,50,50,verde);

	}else if(j2[0] == 3){

		FillRect(205,60,50,50,naranja);

	}else if(j2[0] == 4){

	    FillRect(65,130,50,50,amarillo);

	}else if(j2[0] == 5){

	    FillRect(135,130,50,50,rojo);

	}else if(j2[0] == 6){

		FillRect(205,130,50,50,rosa);
	}

}
void cool1(void){
	if(cd1 == 0){
		LCD_Print("0", 260,5,2,colorj1,0x0000);
		HAL_TIM_Base_Stop_IT(&htim14);
	}else if(cd1 == 1){
		LCD_Print("1", 260,5,2,colorj1,0x0000);
	}else if(cd1 == 2){
		LCD_Print("2", 260,5,2,colorj1,0x0000);
	}else if(cd1 == 3){
		LCD_Print("3", 260,5,2,colorj1,0x0000);
	}else if(cd1 == 4){
		LCD_Print("4", 260,5,2,colorj1,0x0000);
	}else if(cd1 == 5){
		LCD_Print("5", 260,5,2,colorj1,0x0000);
	}else if(cd1 == 6){
		LCD_Print("6", 260,5,2,colorj1,0x0000);
	}else if(cd1 == 7){
		LCD_Print("7", 260,5,2,colorj1,0x0000);
	}else if(cd1 == 8){
		LCD_Print("8", 260,5,2,colorj1,0x0000);
	}
}
void cool2(void){
	if(cd2 == 0){
		LCD_Print("0", 260,210,2,colorj2,0x0000);
		HAL_TIM_Base_Stop_IT(&htim13);
	}else if(cd2 == 1){
		LCD_Print("1", 260,210,2,colorj2,0x0000);
	}else if(cd2 == 2){
		LCD_Print("2", 260,210,2,colorj2,0x0000);
	}else if(cd2 == 3){
		LCD_Print("3", 260,210,2,colorj2,0x0000);
	}else if(cd2 == 4){
		LCD_Print("4", 260,210,2,colorj2,0x0000);
	}else if(cd2 == 5){
		LCD_Print("5", 260,210,2,colorj2,0x0000);
	}else if(cd2 == 6){
		LCD_Print("6", 260,210,2,colorj2,0x0000);
	}else if(cd2 == 7){
		LCD_Print("7", 260,210,2,colorj2,0x0000);
	}else if(cd2 == 8){
		LCD_Print("8", 260,210,2,colorj2,0x0000);
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	if(state == 3){
		c = 1;
	}
	if(RX[0] == 'f'){
		if(state == 3){
			if(cd1 == 0){
				cd1 = 8;
				HAL_TIM_Base_Start_IT(&htim14);
			}
		}else if(state == 0 || state == 5){
			state = 6;
		}else if(state == 6){
			state = 7;
		}

	}
	if(RX[0] == 'k'){
		if(state == 3){
			if(cd2 == 0){
				cd2 = 8;
				HAL_TIM_Base_Start_IT(&htim13);
			}
		}else if(state == 0 || state == 5){
			state = 6;
		}else if(state == 6){
			state = 7;
		}

	}
	if(RX[0] == 'e'){
		if(state == 0 || state == 5){
			state = 2;
		}else if(state == 6){
			state = 7;
		}else if(state == 7){
			j1[2] = 1;
		}

	}
	if(RX[0] == 'u'){
		if(state == 1 || state == 5){
			state = 2;
		}else if(state == 6){
			state = 7;
		}else if(state == 7){
			j2[2] = 1;
		}

	}
	if(RX[0] == 'w'){//arriba
		if(state == 7){
			if(j1[1] == 4){
				if(j2[1] == 1){
					//no hace nada
				}else{
					j1[0] = j1[1];
					j1[1] = 1;
				}
			}else if(j1[1] == 5){
				if(j2[1] == 2){

				}else{
					j1[0] = j1[1];
					j1[1] = 2;
				}
			}else if(j1[1] == 6){
				if(j2[1] == 3){

				}else{
					j1[0] = j1[1];
					j1[1] = 3;
				}

			}

		}

		//linea = 0;
		if(state == 3){
			n2++;
			FillRect(movex,movey,x,2,0x0000);
			FillRect(movex,movey+2,x,2,rastroj1);
			FillRect(movex,movey+4,x,1,0xFFFF);
			FillRect(movex,movey+5,x,2,rastroj1);
			FillRect(movex,movey+7,x,2,0x0000);
			x = g;
			y = l;
			if (abajo != 2){
				arriba = 2;
			}

			if (derecha != 0){
				derecha--;
			}
			/*if (abajo != 0){
				abajo--;
			}*/

			if (izquierda != 0){
				izquierda--;
			}

			if (derecha == 1){

				yy[n2] = movey + 4;
				xf[n2] = movex+d+4;

				xi[n2] = xx[n1];

				//originx = movex+d+4;
				movex = movex + d;
				movey = movey - d;

			}
			if (izquierda == 1){

				yy[n2] = movey+4;
				xf[n2] = movex+4;
				xi[n2] = xx[n1];

				//originx = movex+4;
				movey = movey - d;
			}
		}



	}
	if(RX[0] == 's'){//abajo
		if(state == 7){
			if(j1[1] == 1){
				if(j2[1] == 4){
					//no hace nada
				}else{
					j1[0] = j1[1];
					j1[1] = 4;
				}
			}else if(j1[1] == 2){
				if(j2[1] == 5){
					//no hace nadaa
				}else{
					j1[0] = j1[1];
					j1[1] = 5;
				}
			}else if(j1[1] == 3){
				if(j2[1] == 6){
					//no hace nada
				}else{
					j1[0] = j1[1];
					j1[1] = 6;
				}

			}
		}
		if(state == 3){
			n2++;
			//linea = 0;
			FillRect(movex,movey,x,2,0x0000);
			FillRect(movex,movey+2,x,2,rastroj1);
			FillRect(movex,movey+4,x,1,0xFFFF);
			FillRect(movex,movey+5,x,2,rastroj1);
			FillRect(movex,movey+7,x,2,0x0000);
			x = g;
			y = l;

			if (arriba != 2){
				abajo = 2;
			}

			/*if (arriba != 0){
				arriba--;
			}*/
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
				//H_line(xi[n2],yy[n2],abs(xf[n2]-xi[n2]),0xFFFF);


				//originx=movex+d+4;
				//originy=movey;
				movex = movex + d;
			}
			if(izquierda == 1){

				yy[n2] = movey+4;
				xf[n2] = movex+4;
				xi[n2] = xx[n1];
				//H_line(xf[n2],yy[n2],abs(xf[n2]-xi[n2]),0xFFFF);
				//originx=movex+4;
				//originy = movey;
			}
		}

	}
	if(RX[0] == 'a'){//izquierda
		if(state == 7){
			if(j1[1] != 1 && j1[1] != 4){
				if(j2[1] == j1[1]-1){
					if(j1[1] == 2){
						if(j2[1] == 1){
							//no hace nada
						}
					}else if(j1[1] == 5){
						if(j2[1] == 4){
							//no hace nada
						}
					}else if(j1[1] == 3){
						if(j2[1] == 2){
							j1[0] = j1[1];
							j1[1] = 1;
						}
					}else if(j1[1] == 6){
						if(j2[1] == 5){
							j1[0] = j1[1];
							j1[1] = 4;
						}
					}
				}else{
					j1[0] = j1[1];
					j1[1] -= 1;
				}

			}
		}
		if(state == 3){
			//linea = 0;
			n1++;
			FillRect(movex,movey,2,y,0x0000);
			FillRect(movex+2,movey,2,y,rastroj1);
			FillRect(movex+4,movey,1,y,0xFFFF);
			FillRect(movex+5,movey,2,y,rastroj1);
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

			/*if (derecha != 0){
				derecha--;
			}*/

			if (arriba == 1){

				xx[n1] = movex+4;
				yf[n1] = movey + 4;
				yi[n1] = yy[n2];

				movex = movex - d;
				//originy = movey+4;

			}
			if (abajo == 1){

				xx[n1] = movex+4;
				yf[n1] = movey+d+4;
				yi[n1] = yy[n2];

				//originy = movey+d+4;

				movex = movex - d;
				movey = movey + d;
			}
		}
	}
	if(RX[0] == 'd'){//derecha
		if(state == 7){
			if(j1[1] != 3 && j1[1] != 6){
				if(j2[1] == j1[1]+1){
					if(j1[1] == 1){
						if(j2[1] == 2){
							j1[0] = j1[1];
							j1[1] = 3;
						}
					}else if(j1[1] == 4){
						if(j2[1] == 5){
							j1[0] = j1[1];
							j1[1] = 6;
						}
					}else if(j1[1] == 2){
						if(j2[1] == 3){
							//no hace nada
						}
					}else if(j1[1] == 5){
						if(j2[1] == 6){
							//no hace nada
						}
					}
				}else{
					j1[0] = j1[1];
					j1[1]+=1;
				}
			}
		}
		if(state == 3){
			//linea = 0;
			n1++;
			FillRect(movex,movey,2,y,0x0000);
			FillRect(movex+2,movey,2,y,rastroj1);
			FillRect(movex+4,movey,1,y,0xFFFF);
			FillRect(movex+5,movey,2,y,rastroj1);
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

			/*if (izquierda != 0){
				izquierda--;
			}*/
			if (abajo == 1){

				xx[n1] = movex+4;
				yf[n1] = movey+d+4;
				yi[n1] = yy[n2];

				//originy=movey+4+d;
				movey = movey + d;
				//originx = movex;

			}
			if(arriba == 1){

				xx[n1] = movex+4;
				yf[n1] = movey + 4;
				yi[n1] = yy[n2];

				//originy = movey+4;
				//originx = movex;
			}
		}
	}

//************************************************************************************************
//***********************************Jugador 2****************************************************
//************************************************************************************************
	if(RX[0] == 'y'){//arriba j2
		if(state == 7){
			if(j2[1] == 4){
				if(j1[1] == 1){
					//no hace nada
				}else{
					j2[0] = j2[1];
					j2[1] = 1;
				}
			}else if(j2[1] == 5){
				if(j1[1] == 2){

				}else{
					j2[0] = j2[1];
					j2[1] = 2;
				}
			}else if(j2[1] == 6){
				if(j1[1] == 3){

				}else{
					j2[0] = j2[1];
					j2[1] = 3;
				}

			}
		}
		if(state == 3){
			n4++;
			//linea2 = 0;
			FillRect(movex2,movey2,x2,2,0x0000);
			FillRect(movex2,movey2+2,x2,2,rastroj2);
			FillRect(movex2,movey2+4,x2,1,0xFFFF);
			FillRect(movex2,movey2+5,x2,2,rastroj2);
			FillRect(movex2,movey2+7,x2,2,0x0000);
			x2 = g;
			y2 = l;
			if (abajo2 != 2){
				arriba2 = 2;
			}

			if (derecha2 != 0){
				derecha2--;
			}
			/*if (abajo2 != 0){
				abajo2--;
			}*/

			if (izquierda2 != 0){
				izquierda2--;
			}

			if (derecha2 == 1){

				yy2[n4] = movey2 + 4;
				xf2[n4] = movex2+d+4;
				xi2[n4] = xx2[n3];

				//originx2 = movex2+d+4;
				movex2 = movex2 + d;
				movey2 = movey2 - d;

			}
			if (izquierda2 == 1){

				yy2[n4] = movey2+4;
				xf2[n4] = movex2+4;
				xi2[n4] = xx2[n3];

				//originx2 = movex2+4;
				movey2 = movey2 - d;
			}
		}


	}
	if(RX[0] == 'h'){//abajo j2
		if(state == 7){
			if(j2[1] == 1){
				if(j1[1] == 4){
					//no hace nada
				}else{
					j2[0] = j2[1];
					j2[1] = 4;
				}
			}else if(j2[1] == 2){
				if(j1[1] == 5){
					//no hace nadaa
				}else{
					j2[0] = j2[1];
					j2[1] = 5;
				}
			}else if(j2[1] == 3){
				if(j1[1] == 6){
					//no hace nada
				}else{
					j2[0] = j2[1];
					j2[1] = 6;
				}

			}
		}
		if(state == 3){
			n4++;
			//linea2 = 0;
			FillRect(movex2,movey2,x2,2,0x0000);
			FillRect(movex2,movey2+2,x2,2,rastroj2);
			FillRect(movex2,movey2+4,x2,1,0xFFFF);
			FillRect(movex2,movey2+5,x2,2,rastroj2);
			FillRect(movex2,movey2+7,x2,2,0x0000);
			x2 = g;
			y2 = l;

			if (arriba2 != 2){
				abajo2 = 2;
			}

			/*if (arriba2 != 0){
				arriba2--;
			}*/
			if (derecha2 != 0){
				derecha2--;
			}

			if (izquierda2 != 0){
				izquierda2--;
			}

			if (derecha2 == 1){
				yy2[n4] = movey2 + 4;
				xf2[n4] = movex2+d+4;
				xi2[n4] = xx2[n3];



				//originx2=movex2+d+4;
				//originy2=movey2;
				movex2 = movex2 + d;
			}
			if(izquierda == 1){

				yy2[n4] = movey2+4;
				xf2[n4] = movex2+4;
				xi2[n4] = xx2[n3];

				//originx2=movex2+4;
				//originy2 = movey2;
			}
		}

	}
	if(RX[0] == 'j'){//derecha j2
		if(state == 7){
			if(j2[1] != 3 && j2[1] != 6){
				if(j1[1] == j2[1]+1){
					if(j2[1] == 1){
						if(j1[1] == 2){
							j2[0] = j2[1];
							j2[1] = 3;
						}
					}else if(j2[1] == 4){
						if(j1[1] == 5){
							j2[0] = j2[1];
							j2[1] = 6;
						}
					}else if(j2[1] == 2){
						if(j1[1] == 3){
							//no hace nada
						}
					}else if(j2[1] == 5){
						if(j1[1] == 6){
							//no hace nada
						}
					}
				}else{
					j2[0] = j2[1];
					j2[1]+=1;
				}
			}
		}
		if(state == 3){
			//linea2 = 0;
			n3++;
			FillRect(movex2,movey2,2,y2,0x0000);
			FillRect(movex2+2,movey2,2,y2,rastroj2);
			FillRect(movex2+4,movey2,1,y2,0xFFFF);
			FillRect(movex2+5,movey2,2,y2,rastroj2);
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

			/*if (izquierda2 != 0){
				izquierda2--;
			}*/
			if (abajo2 == 1){

				xx2[n3] = movex2+4;
				yf2[n3] = movey2+d+4;
				yi2[n3] = yy2[n4];

				//originy2=movey2+4+d;
				movey2 = movey2 + d;
				//originx2 = movex2;

			}
			if(arriba2 == 1){

				xx2[n3] = movex2+4;
				yf2[n3] = movey2 + 4;
				yi2[n3] = yy2[n4];

				//originy2 = movey2+4;
				//originx2 = movex2;
			}
		}

	}
	if(RX[0] == 'g'){//izquierda j2
		if(state == 7){
			if(j2[1] != 1 && j2[1] != 4){
				if(j1[1] == j2[1]-1){
					if(j2[1] == 2){
						if(j1[1] == 1){
							//no hace nada
						}
					}else if(j2[1] == 5){
						if(j1[1] == 4){
							//no hace nada
						}
					}else if(j2[1] == 3){
						if(j1[1] == 2){
							j2[0] = j2[1];
							j2[1] = 1;
						}
					}else if(j2[1] == 6){
						if(j1[1] == 5){
							j2[0] = j2[1];
							j2[1] = 4;
						}
					}
				}else{
					j2[0] = j2[1];
					j2[1] -= 1;
				}

			}
		}
		if(state == 3){
			//linea2 = 0;
			n3++;
			FillRect(movex2,movey2,2,y2,0x0000);
			FillRect(movex2+2,movey2,2,y2,rastroj2);
			FillRect(movex2+4,movey2,1,y2,0xFFFF);
			FillRect(movex2+5,movey2,2,y2,rastroj2);
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

			/*if (derecha2 != 0){
				derecha2--;
			}*/

			if (arriba2 == 1){

				xx2[n3] = movex2+4;
				yf2[n3] = movey2 + 4;
				yi2[n3] = yy2[n4];

				movex2 = movex2 - d;
				//originy2 = movey2+4;

			}
			if (abajo2 == 1){

				xx2[n3] = movex2+4;
				yf2[n3] = movey2+d+4;
				yi2[n3] = yy2[n4];

				//originy2 = movey2+d+4;

				movex2 = movex2 - d;
				movey2 = movey2 + d;
			}
		}

	}


	HAL_UART_Receive_IT(&huart2, RX, 1);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim14){
		cd1--;
	}else if(htim == &htim13){
		cd2--;
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
