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
#include "time.h"
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
int moveDown(int x, int y, int type[][4], uint16_t color);
int change(int type,int x,int y);
int create();
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int type1[][4] = { { 0, 0, 0, 0 }, { 1, 1, 1, 0 }, { 0, 1, 0, 0 },
		{ 0, 0, 0, 0 } };
int type2[][4] = { { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 1, 0 },
		{ 0, 0, 0, 0 } };
//int type2[][3] = { { 1, 1, 0 }, { 0, 1, 1 }, { 0, 0, 1 } };
int type3[][4] = { { 0, 0, 0, 0 }, { 1, 1, 0, 0 }, { 0, 1, 1, 0 },
		{ 0, 0, 0, 0 } };
int type4[][4] = { { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 },
		{ 0, 0, 0, 0 } };
int type5[][4] = { { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 },
		{ 0, 1, 0, 0 } };
int type0[][4] = { { 0, 0, 0, 0 },{ 1, 1, 1, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }
		 };
int shapeType = 0; //0代表使用3*3矩阵的形状，1代表正方形，2代表长条
uint16_t container[31][20];
uint16_t color;
int pre;
int base[4][4];
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

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
	time_t ts;
	unsigned seed;
	seed = time(0);
	srand(seed);
	InitialPlane();
	uint16_t x = 0;
	uint16_t y = 10;
	uint16_t tmp = 0;

	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 20; j++) {
			container[i][j] = 0;
		}
	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	int t = 0;
	while (1) {
		x = 0;
		y = rand()%18;

		int idx = create();
//		idx = 0;
		switch (idx) {
		case 0:
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					base[i][j] = type0[i][j];
				}
			}
			break;
		case 1:
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					base[i][j] = type1[i][j];
				}
			}
			break;
		case 2:
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					base[i][j] = type2[i][j];
				}
			}
			break;
		case 3:
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					base[i][j] = type3[i][j];
				}
			}
			break;
		case 4:
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					base[i][j] = type4[i][j];
				}
			}
			break;
		}

		LCD_ShowNum(20, 40, t, 4, 12);
		t++;

		if (GameOver(x, y, base) == 0) {
			drawPlane(x, y, base, color);
			record(x, y, base);
		} else {
			LCD_ShowString(31, 40, 200, 24, 24, (uint8_t*) "Game Over!");
			break;
		}
		HAL_Delay(400);
//		drawPlane(x, y, type1, BLUE);
		int breakOrNot = 0;
		int tt = 0;
		int shape = idx;

		while (breakOrNot == 0) {
			LCD_ShowNum(20, 60, tt++, 4, 12);
			HAL_Delay(100);
			shape = change(shape,x,y);
			int state = moveDown(x, y, base, color);
			if (state == 1) {
				x++;
			} else {
				breakOrNot = 1;
			}
		}
	}
	/* USER CODE END WHILE */
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


int change(int type,int x,int y) {
	int sum = 0;
	int tmp[4][4];
	if (type == 0) {
		type = 5;
		for(int i=0;i<31;i++){
			for(int j=0;j<20;j++){
				if(container[i][j]==1){
					sum += 1;
				}
			}
		}
		delete(x,y,base);
		record(x,y,type5);
		for(int i=0;i<31;i++){
			for(int j=0;j<20;j++){
				if(container[i][j]==1){
					sum -= 1;
				}
			}
		}
		if(sum==0){//无碰撞
			clearPlane(x,y,base);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					base[i][j] = type5[i][j];
				}
			}
			drawPlane(x,y,base,color);
		}else{
			delete(x,y,type5);
			record(x,y,base);
		}


	} else if (type == 5) {
		type = 0;
		for(int i=0;i<31;i++){
			for(int j=0;j<20;j++){
				if(container[i][j]==1){
					sum += 1;
				}
			}
		}
		delete(x,y,base);

		record(x,y,type0);
		for(int i=0;i<31;i++){
			for(int j=0;j<20;j++){
				if(container[i][j]==1){
					sum -= 1;
				}
			}
		}
		if(sum==0){//无碰撞
			clearPlane(x,y,base);
			drawPlane(x,y,type0,color);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					base[i][j] = type0[i][j];
				}
			}

		}else{
			delete(x,y,type0);
			record(x,y,base);
		}

	} else if (type == 4) {
	} else {
		for(int i=0;i<31;i++){
			for(int j=0;j<20;j++){
				if(container[i][j]==1){
					sum += 1;
				}
			}
		}

		delete(x,y,base);
		int ans[4][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0,
				0, 0, 0 } };
		ans[0][2] = base[0][0];
		ans[0][0] = base[2][0];
		ans[2][0] = base[2][2];
		ans[2][2] = base[0][2];
		ans[0][1] = base[1][0];
		ans[1][2] = base[0][1];
		ans[2][1] = base[1][2];
		ans[1][0] = base[2][1];
		record(x,y,ans);
		for(int i=0;i<31;i++){
			for(int j=0;j<20;j++){
				if(container[i][j]==1){
					sum -= 1;
				}
			}
		}
		if(sum==0){//无碰撞
			clearPlane(x,y,base);
			drawPlane(x,y,ans,color);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					base[i][j] = ans[i][j];
				}
			}
		}else{
			delete(x,y,ans);
			record(x,y,base);
		}
	}
	return type;
}
/*
 * 随机函数，保证不出现上一次出现过的类型
 * 随机得到旋转的角度
 * 利用上面提到的旋转函数进行转化
 * 顺便取得作画时所用的颜色
 */
int create() {

	int now = rand() % 5;
	while (now == pre) {
		now = rand() % 5;
	}
	pre = now;
	//int type = rand() % 4;
	if (now == 0) {
		color = BLUE;
		//return type0;
	}
	if (now == 1) {
		color = YELLOW;
		//return type1;
	}
	if (now == 2) {
		color = RED;
		//return type2;
	}
	if (now == 3) {
		color = GREEN;
		//return type3;
	}
	if (now == 4) {
		color = BRRED;
		//return type4;
	}
	return now;
}
/*
 * 返回1代表GameOver
 * 返回0代表继续
 */
int GameOver(int x, int y, int type[][4]) {
	int sum = 0;
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 20; j++) {
			sum += container[i][j];
		}
	}
	record(x, y, type);
	int sum2 = 0;
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 20; j++) {
			sum2 += container[i][j];
		}
	}
	LCD_ShowNum(20, 20, (sum2 - sum), 4, 12);
	if (sum2 - sum != 4) {
		return 1;
	} else {
		delete(x, y, type);
	}
	return 0;
}
/*
 * 将当前位置(x,y)的形状写入container
 */
void record(int x, int y, int type[][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (type[i][j] == 1 && x + i < 31 && y + j < 20 && x + i >= 0
					&& y + j >= 0) {
				container[x + i][y + j] = 1;
			}
		}
	}
}
/*
 * 将container位置(x,y)的形状删除
 */
void delete(int x, int y, int type[][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (type[i][j] == 1 && x + i < 31 && y + j < 20 && x + i >= 0
					&& y + j >= 0) {
				container[x + i][y + j] = 0;
			}
		}
	}
}
/*
 * 将方块向下移动
 * 返回值表示有没有走到底，0表示到底了，1表示还没有
 */
int moveDown(int x, int y, int type[][4], uint16_t color) {
	if (checkCrash(x, y, type, 0) == 0) {
		clearPlane(x, y, type);
		drawPlane(x + 1, y, type, color);
		return 1;
	} else {
		return 0;
	}
}

/*
 * 检查碰撞，direction是行动方向，0 = down，1 = left，2 = right
 * 有碰撞则返回1，无则返回0
 */
int checkCrash(int x, int y, int type[][4], int direction) {
	int sum = 0;
	switch (direction) {
	case 0:	//down
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 20; j++) {
				sum += container[i][j];
			}
		}
		delete(x, y, type);
		record(x + 1, y, type);
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 20; j++) {
				sum -= container[i][j];
			}
		}
		if (sum == 0) {
			return 0;
		} else {
			delete(x + 1, y, type);
			record(x, y, type);
			return 1;
		}
		break;
	case 1:	//left
		sum = 0;
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 20; j++) {
				sum += container[i][j];
			}
		}
		delete(x, y, type);
		record(x, y + 1, type);
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 20; j++) {
				sum -= container[i][j];
			}
		}
		delete(x, y + 1, type);
		record(x, y, type);
		if (sum == 0) {
			return 0;
		} else {
			return 1;
		}
		break;
	case 2:	//right
		sum = 0;
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 20; j++) {
				sum += container[i][j];
			}
		}
		delete(x, y, type);
		record(x, y - 1, type);
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 20; j++) {
				sum -= container[i][j];
			}
		}
		delete(x, y - 1, type);
		record(x, y, type);
		if (sum == 0) {
			return 0;
		} else {
			return 1;
		}
		break;
	}
}
/*
 * 初始化画布和基础布局
 */
void InitialPlane() {
//	LCD_Set_Window(0,0,165,253);
	LCD_DrawRectangle(0, 248, 160, 253);
	LCD_DrawRectangle(160, 0, 165, 253);
	LCD_DrawLine(160, 248, 165, 248);
//	LCD_Color_Fill(0,250,160,255,CYAN);
//	LCD_Color_Fill(160,0,165,255,BRRED);
//	LCD_Clear(GRAY);
}
/*
 * 在画布的位置(x,y)加入有形状的方块组
 */
void drawPlane(uint16_t x, uint16_t y, int array[][4], uint16_t color) {
//	LCD_ShowNum(31, 40,array[0][0],2, 24);
	for (uint16_t i = 0; i < 4; i++) {
		for (uint16_t j = 0; j < 4; j++) {
			if (array[i][j] == 1) {
				DrawPoint(y + j, x + i, color);
			}
		}
	}
}
/*
 * 在画布的位置(x,y)擦除方块组
 */
void clearPlane(uint16_t x, uint16_t y, int array[][4]) {
//	LCD_ShowNum(31, 40,array[0][0],2, 24);
	for (uint16_t i = 0; i < 4; i++) {
		for (uint16_t j = 0; j < 4; j++) {
			if (array[i][j] == 1) {
				ClearPoint(y + j, x + i);
			}
		}
	}
	InitialPlane();
}
/*
 * 像素放大，每一个方块是8*8像素点的集合。
 */
void DrawPoint(uint16_t x1, uint16_t y1, uint16_t color) {
	for (uint16_t i = x1 * 8; i < x1 * 8 + 8; i++) {
		for (uint16_t j = y1 * 8; j < y1 * 8 + 8; j++) {
			LCD_Fast_DrawPoint(i, j, color);
		}
	}

	for (uint16_t i = x1 * 8; i < x1 * 8 + 8; i++) {
		LCD_Fast_DrawPoint(i, y1 * 8, BLACK);
		LCD_Fast_DrawPoint(i, y1 * 8 + 8, BLACK);
		LCD_Fast_DrawPoint(x1 * 8, (y1 * 8 + (i - x1 * 8)), BLACK);
		LCD_Fast_DrawPoint((x1 * 8 + 8), (y1 * 8 + (i - x1 * 8)), BLACK);
	}
}
/*
 * 将方块擦除
 */
void ClearPoint(uint16_t x1, uint16_t y1) {
	for (uint16_t i = x1 * 8; i < x1 * 8 + 8; i++) {
		for (uint16_t j = y1 * 8; j < y1 * 8 + 8; j++) {
			LCD_Fast_DrawPoint(i, j, WHITE);
		}
	}

	for (uint16_t i = x1 * 8; i < x1 * 8 + 8; i++) {
		LCD_Fast_DrawPoint(i, y1 * 8, WHITE);
		LCD_Fast_DrawPoint(i, y1 * 8 + 8, WHITE);
		LCD_Fast_DrawPoint(x1 * 8, (y1 * 8 + (i - x1 * 8)), WHITE);
		LCD_Fast_DrawPoint((x1 * 8 + 8), (y1 * 8 + (i - x1 * 8)), WHITE);
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
