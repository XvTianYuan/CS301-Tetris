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
#include "lcd.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
int moveDown(int x,int y,int type[][3],uint16_t color);
int* change(int type,int kind);
int* random();
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int type1[4][4] = { { 0, 0, 0 ,0}, { 1, 1, 1,0 }, { 0, 1, 0,0 },{0,0,0,0} };
int type2[4][4] = { { 0, 1, 0,0 }, { 0, 1, 0,0 }, { 0, 1, 1,0 },{0,0,0,0} };
//int type2[][3] = { { 1, 1, 0 }, { 0, 1, 1 }, { 0, 0, 1 } };
int type3[4][4] = { { 0, 0, 0,0 }, { 1, 1, 0,0 }, { 0, 1, 1,0 },{0,0,0,0} };
int type4[4][4] = { { 1, 1, 0,0 }, { 1, 1, 0 ,0}, { 0, 0, 0 ,0},{0,0,0,0} };
int type0[4][4] = {{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}};
int type5[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,1,1,1}};
int shapeType = 0;//0代表使用3*3矩阵的形状，1代表长条
uint16_t container[30][18];
uint16_t color;
int pre;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */
	srand((unsigned)time(NULL));
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	LCD_Init();
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	/* USER CODE BEGIN 2 */
	InitialPlane();
	uint16_t x = 0;
	uint16_t y = 10;
	uint16_t tmp = 0;

//	for(int i = 0; i<30; i++){
//		container[i][0] = 1;
//		container[i][17] = 1;
//	}
//	for(int j = 0; j<18; j++){
//		container[27][j] = 1;
//	}
	for(int i = 0; i<30; i++){
		for(int j = 0; j <18; j++){
			container[i][j] = 0;
		}
	}
	pre=-1;
	color=0;
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		x = 0;
		y = 10;
//		if(GameOver(x,y,type2)==0){
//			drawPlane(x, y, type2, BLUE);
//		}else{
//			LCD_ShowString(50,40,200,50,32,(uint8_t)"Game Over!");
//			break;
//		}
        int base[4][4]=create();
		drawPlane(x, y, base, color);
		int breakOrNot = 0;
		while(breakOrNot==0){
			switch (shapeType){
				case 0:
					HAL_Delay(100);
					int state = moveDown(x,y,base,color);
					if(state == 1){
						x++;
					}else{
						breakOrNot = 1;
					}
	//				drawPlane(x, y, type2, RED);
	//				HAL_Delay(100);
	//				clearPlane(x,y,type2);
					break;
				case 1:
					drawPlane2(x, y, color, 0);
					HAL_Delay(100);
					clearPlane2(x, y,0);
					break;
			}
		}
	}

	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;

}

/* USER CODE BEGIN 4 */

int* change(int type,int kind){
     if(type==0){
		 type=5;
		return type5;
	 }
	 else if(type==5){
		 type=0;
		 return type0;
	 }
	 else if(type==4){
		 return type4;
	 }
	 else{
		 int base[4][4]={};
		 int ans[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
		 if(type==1) base=type1;
		 if(type==2) base=type2;
		 if(type==3) base=type3;
	     ans[0][2]=base[0][0];
		 ans[0][0]=base[2][0];
		 ans[2][0]=base[2][2];
		 ans[2][2]=base[0][2];
    	 ans[0][1]=base[1][0];
		 ans[1][2]=base[0][1];
		 ans[2][1]=base[1][2];
		 ans[1][0]=base[2][1];
		 return ans;
	 }
}
/*
 * 随机函数，保证不出现上一次出现过的类型
 * 随机得到旋转的角度
 * 利用上面提到的旋转函数进行转化
 * 顺便取得作画时所用的颜色
 */	
int* create(){
	int now=rand()%5;
	while(now==pre){
		now=rand()%5;
	}
	pre=now;
	color=now+1;
	int type=rand()%4;
	if(type==0) {
		color=BLUE;
		return type0;
	}
	if(type==1) {
		color=YELLOW;
		return type1;
	}
	if(type==2) {
		color=RED;
		return type2;
	}
	if(type==3) {
		color=GREEN;
		return type3;
	}
	if(type==4) {
		color=BRRED;
		return type4;
	}
}
/*
 * 返回1代表GameOver
 * 返回0代表继续
 */
int GameOver(int x,int y,int type[][3]){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(container[x+i][y+j]==1 && type[i][j]==1){
				return 1;
			}
		}
	}
	return 0;
}

void record(int x,int y,int type[][3]){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(type[i][j]==1 && x+i<30 && y+j<18 && x+i >= 0 && y+j>=0){
				container[x+i][y+j]=1;
			}
		}
	}
}
void delete(int x,int y,int type[][3]){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(type[i][j]==1 && x+i<30 && y+j<18 && x+i >= 0 && y+j>=0){
				container[x+i][y+j]=0;
			}
		}
	}
}
/*
 * 将方块向下移动
 * 返回值表示有没有走到底，0表示到底了，1表示还没有
 */
int moveDown(int x,int y,int type[][3],uint16_t color){
	if(checkCrash(x,y,type,0)==0){
		clearPlane(x,y,type);
		drawPlane(x+1,y,type,color);
		return 1;
	}else{
		return 0;
	}
}
/*
 * 检查碰撞，direction是行动方向，0 = down，1 = left，2 = right
 * 有碰撞则返回1，无则返回0
 */
int checkCrash(int x,int y,int type[][3],int direction){
	int sum = 0;
	switch(direction){
	case 0://down
		for(int i=0;i<30;i++){
			for(int j=0;j<18;j++){
				sum += container[i][j];
			}
		}
		delete(x,y,type);
		record(x+1,y,type);
		for(int i=0;i<30;i++){
			for(int j=0;j<18;j++){
				sum -= container[i][j];
			}
		}
		if(sum == 0){
			return 0;
		}else{
			delete(x+1,y,type);
			record(x,y,type);
			return 1;
		}
		break;
	case 1://left
		sum = 0;
		for(int i=0;i<30;i++){
			for(int j=0;j<18;j++){
				sum += container[i][j];
			}
		}
		delete(x,y,type);
		record(x,y+1,type);
		for(int i=0;i<30;i++){
			for(int j=0;j<18;j++){
				sum -= container[i][j];
			}
		}
		delete(x,y+1,type);
		record(x,y,type);
		if(sum == 0){
			return 0;
		}else{
			return 1;
		}
		break;
	case 2://right
		sum = 0;
		for(int i=0;i<30;i++){
			for(int j=0;j<18;j++){
				sum += container[i][j];
			}
		}
		delete(x,y,type);
		record(x,y-1,type);
		for(int i=0;i<30;i++){
			for(int j=0;j<18;j++){
				sum -= container[i][j];
			}
		}
		delete(x,y-1,type);
		record(x,y,type);
		if(sum == 0){
			return 0;
		}else{
			return 1;
		}
		break;
	}
}
void InitialPlane(){
	LCD_Set_Window(0,0,165,253);
	LCD_DrawRectangle(0,248,160,253);
	LCD_DrawRectangle(160,0,165,253);
	LCD_DrawLine(160, 248, 165, 248);
//	LCD_Color_Fill(0,250,160,255,CYAN);
//	LCD_Color_Fill(160,0,165,255,BRRED);
//	LCD_Clear(GRAY);
}

void drawPlane(uint16_t x, uint16_t y, int array[][3], uint16_t color) {
//	LCD_ShowNum(30, 40,array[0][0],2, 24);
	for (uint16_t i = 0; i < 3; i++) {
		for (uint16_t j = 0; j < 3; j++) {
			if (array[i][j] == 1) {
				DrawPoint(y + j, x + i, color);
			}
		}
	}
}
void clearPlane(uint16_t x, uint16_t y, int array[][3]) {
//	LCD_ShowNum(30, 40,array[0][0],2, 24);
	for (uint16_t i = 0; i < 3; i++) {
		for (uint16_t j = 0; j < 3; j++) {
			if (array[i][j] == 1) {
				ClearPoint(y + j, x + i);
			}
		}
	}
	InitialPlane();
}

void drawPlane2(uint16_t x, uint16_t y,uint16_t color, int type){
	if(type == 0){
		for (uint16_t i = x; i < x + 4; i++) {
			DrawPoint(i, y+1, color);
		}
	}else if(type == 1){
		for (uint16_t i = y; i < y + 4; i++) {
			DrawPoint(x+1, i, color);
		}
	}

}
void clearPlane2(uint16_t x, uint16_t y, int type){
	if(type == 0){
		for (uint16_t i = x; i < x + 4; i++) {
			ClearPoint(i, y+1);
		}
	}else if(type == 1){
		for (uint16_t i = y; i < y + 4; i++) {
			ClearPoint(x+1, i);
		}
	}
	InitialPlane();

}

void DrawPoint(uint16_t x1, uint16_t y1, uint16_t color) {
	for (uint16_t i = x1 * 8; i < x1 * 8 + 8; i++) {
		for (uint16_t j = y1 * 8; j < y1 * 8 + 8; j++) {
			LCD_Fast_DrawPoint(i, j, color);
		}
	}

	for (uint16_t i= x1*8;i < x1*8 + 8; i++){
		LCD_Fast_DrawPoint(i,y1*8,BLACK);
		LCD_Fast_DrawPoint(i,y1*8+8,BLACK);
		LCD_Fast_DrawPoint(x1*8,(y1*8+(i-x1*8)),BLACK);
		LCD_Fast_DrawPoint((x1*8+8),(y1*8+(i-x1*8)),BLACK);
	}
}
void ClearPoint(uint16_t x1, uint16_t y1) {
	for (uint16_t i = x1 * 8; i < x1 * 8 + 8; i++) {
		for (uint16_t j = y1 * 8; j < y1 * 8 + 8; j++) {
			LCD_Fast_DrawPoint(i, j, WHITE);
		}
	}

	for (uint16_t i= x1*8;i < x1*8 + 8; i++){
		LCD_Fast_DrawPoint(i,y1*8,WHITE);
		LCD_Fast_DrawPoint(i,y1*8+8,WHITE);
		LCD_Fast_DrawPoint(x1*8,(y1*8+(i-x1*8)),WHITE);
		LCD_Fast_DrawPoint((x1*8+8),(y1*8+(i-x1*8)),WHITE);
	}
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
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
