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
#include "lcd.h"
#include "time.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void record(int x, int y, int type[][4]);
int GameOver(int x, int y, int type[][4]);
void delete(int x, int y, int type[][4]);
int checkAndDraw(int x, int y, int **type, int direction);
void InitialPlane();
void drawPlane(uint16_t x, uint16_t y, int array[][4], uint16_t color);
void clearPlane(int x, int y, int array[][4]);
void DrawPoint(uint16_t x1, uint16_t y1, uint16_t color);
void ClearPoint(uint16_t x1, uint16_t y1);
int create();
int checkCrash(int x, int y, int type[][4], int direction);
int change();
int moveLeft(int x, int y, int type[][4], uint16_t color);
int moveRight(int x, int y, int type[][4], uint16_t color);
int rotate();
int BcheckCrash(int x, int y, int type[][4], int direction);
void inheritence();
void randomCreateFirstOne();
void createNext(int idxx);
void record2(int x, int y, int type[][4]);
void executeDelete(int x);
void deleteLine(int x);
void recordColor(int x, int y, int type[][4],uint16_t col);
void createNext2(int idxx);

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
int moveDown(int x, int y, int type[][4], uint16_t color);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int type1[][4] = { { 0, 0, 0, 0 }, { 1, 1, 1, 0 }, { 0, 1, 0, 0 },
                   { 0, 0, 0, 0 } };
int type2[][4] = { { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 1, 0 },
                   { 0, 0, 0, 0 } };
int type3[][4] = { { 0, 0, 0, 0 }, { 1, 1, 0, 0 }, { 0, 1, 1, 0 },
                   { 0, 0, 0, 0 } };
int type4[][4] = { { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 },
                   { 0, 0, 0, 0 } };
int type7[][4] = { { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 },
                   { 0, 1, 0, 0 } };
int type5[][4] ={{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}};
int type6[][4] ={{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}};
int type0[][4] = { { 0, 0, 0, 0 }, { 1, 1, 1, 1 }, { 0, 0, 0, 0 },
                   { 0, 0, 0, 0 } };
int shapeType = 0; //0代表使用3*3矩阵的形状，1代表正方形，2代表长条
uint16_t container[31][20];
uint16_t static_container[31][20];
uint16_t colorContainer[31][20];
uint16_t color;
int pre;
int base[4][4];
int next[4][4];

int direction_type;
int nextx=2;
int nexty=23;
int nextIDX;
uint16_t next_color;

int next2[4][4];
int next2x=8;
int next2y=23;
int next2IDX;
uint16_t next_2_color;
int user_score;
int user_level;
double user_delay = 15;
double delay;
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
    int x = 0;
    int y = 10;
    next_color=RED;
    next_2_color=BLUE;
    user_score=0;
    delay=user_delay;
    user_level=1;
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 20; j++) {
            container[i][j] = 0;
        }
    }

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    int t = 0;
    next2IDX=create();


    while (1) {
        x = 0;
        y = 14;
        clearPlane(nextx,nexty,next);
        clearPlane(next2x,next2y,next2);
        color=next_color;
        int idx=nextIDX;
        nextIDX=next2IDX;
        next_color=next_2_color;

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
            case 5:
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        base[i][j] = type5[i][j];
                    }
                }
                break;
            case 6:
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        base[i][j] = type6[i][j];
                    }
                }
                break;
        }

        //LCD_ShowNum(20, 40, t, 4, 12);

        delay = user_delay;
        LCD_ShowString(185, 180, 200, 12, 12, (uint8_t*) "level");
        LCD_ShowNum(183,200,user_level,4,12);
        if (GameOver(x, y, base) == 0) {
            drawPlane(x, y, base, color);
            record(x, y, base);
            next2IDX = create();
            createNext2(next2IDX);
            createNext(nextIDX);
            drawPlane(nextx,nexty,next,next_color);
            drawPlane(next2x,next2y,next2,next_2_color);
        } else {
            LCD_ShowString(31, 40, 200, 24, 24, (uint8_t*) "Game Over!");
            break;
        }
        HAL_Delay(10);
//		drawPlane(x, y, type1, BLUE);
        int breakOrNot = 0;
        int shape = idx;
        if(t%10 == 0){
            LCD_ShowString(30,270,200,24,24, (uint8_t*)"Good luck!");
            delay = 0.4;
        }else{
            LCD_ShowString(30,270,200,24,24, (uint8_t*)"Fighting!!");

        }
        t++;
        while (breakOrNot == 0) {
            //LCD_ShowNum(20, 60, delay, 4, 12);
            HAL_Delay(delay);
            //shape = change(shape, x, y);
            int state = moveDown(x, y, base, color);
            if(state==1)x++;
            for (int i=0;i<user_level;i++){
                state=moveDown(x,y,base,color);
                if(state==1)x++;
            }
            int state2=1;
            int state3=1;
            int state4=1;
            if (state == 1) {
                //x++;
                switch (direction_type){
                    case 1:
                        state2=moveLeft(x,y,base,color);
                        if(state2==1){
                            y--;
                        }
                        direction_type=0;
                        break;
                    case 2:
                        state3=moveRight(x,y,base,color);
                        if(state3==1){
                            y++;
                        }
                        direction_type=0;
                        break;
                    case 3:
                        //rotate();
                        shape = change(shape, x, y);
                        direction_type=0;
                        break;
                    default:
                        break;

                }
            } else {
                record2(x,y,base);
                recordColor(x,y,base,color);
                deleteLine(x);
                breakOrNot = 1;
            }
        }
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */
//shape = change(shape, x, y);

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
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : KEY_WK_Pin */
    GPIO_InitStruct.Pin = KEY_WK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(KEY_WK_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : KEY0_Pin */
    GPIO_InitStruct.Pin = KEY0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY0_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : LED0_Pin */
    GPIO_InitStruct.Pin = LED0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : KEY1_Pin */
    GPIO_InitStruct.Pin = KEY1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY1_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : LED1_Pin */
    GPIO_InitStruct.Pin = LED1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 2);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

int change(int type, int x, int y) {
    int sum = 0;
    int tmp[4][4];
    if (type == 0) {
        type = 7;
        for (int i = 0; i < 31; i++) {
            for (int j = 0; j < 20; j++) {
                if (container[i][j] == 1) {
                    sum += 1;
                }
            }
        }
        delete(x, y, base);
        record(x, y, type7);
        for (int i = 0; i < 31; i++) {
            for (int j = 0; j < 20; j++) {
                if (container[i][j] == 1) {
                    sum -= 1;
                }
            }
        }
        if (sum == 0) { //无碰??
            clearPlane(x, y, base);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    base[i][j] = type7[i][j];
                }
            }
            drawPlane(x, y, base, color);
        } else {
            delete(x, y, type7);
            record(x, y, base);
        }

    } else if (type == 7) {
        type = 0;
        for (int i = 0; i < 31; i++) {
            for (int j = 0; j < 20; j++) {
                if (container[i][j] == 1) {
                    sum += 1;
                }
            }
        }
        delete(x, y, base);

        record(x, y, type0);
        for (int i = 0; i < 31; i++) {
            for (int j = 0; j < 20; j++) {
                if (container[i][j] == 1) {
                    sum -= 1;
                }
            }
        }
        if (sum == 0) { //无碰??
            clearPlane(x, y, base);
            drawPlane(x, y, type0, color);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    base[i][j] = type0[i][j];
                }
            }

        } else {
            delete(x, y, type0);
            record(x, y, base);
        }

    } else if (type == 4) {
    } else {
        for (int i = 0; i < 31; i++) {
            for (int j = 0; j < 20; j++) {
                if (container[i][j] == 1) {
                    sum += 1;
                }
            }
        }

        delete(x, y, base);
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
        ans[1][1] = base[1][1];
        record(x, y, ans);
        for (int i = 0; i < 31; i++) {
            for (int j = 0; j < 20; j++) {
                if (container[i][j] == 1) {
                    sum -= 1;
                }
            }
        }
        if (sum == 0) { //无碰??
            clearPlane(x, y, base);
            drawPlane(x, y, ans, color);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    base[i][j] = ans[i][j];
                }
            }
        } else {
            delete(x, y, ans);
            record(x, y, base);
        }
    }
    return type;
}
/*
 * 随机函数，保证不出现上一次出现过的类??
 * 随机得到旋转的角??
 * 利用上面提到的旋转函数进行转??
 * 顺便取得作画时所用的颜色
 */
int create() {

    int now = rand() % 7;
    while (now == pre) {
        now = rand() % 7;
    }
    pre = now;
    //int type = rand() % 4;
    if (now == 0) {

        next_2_color=BLUE;

    }
    if (now == 1) {

        next_2_color=YELLOW;

    }
    if (now == 2) {

        next_2_color=RED;


    }
    if (now == 3) {
        next_2_color=GREEN;

    }
    if (now == 4) {

        next_2_color=BRRED;
    }
    if(now==5){
        next_2_color=GRAYBLUE;
    }
    if(now==6){
        next_2_color=LIGHTGREEN;
    }
    return now;
}


void createNext(int idxx){
    switch (idxx) {
        case 0:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next[i][j]=type0[i][j];
                }
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next[i][j]=type1[i][j];
                }
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next[i][j]=type2[i][j];
                }
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next[i][j]=type3[i][j];
                }
            }
            break;
        case 4:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next[i][j]=type4[i][j];
                }
            }
            break;
        case 5:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next[i][j]=type5[i][j];
                }
            }
            break;
        case 6:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next[i][j]=type6[i][j];
                }
            }
            break;
    }
}



void createNext2(int idxx){
    switch (idxx) {
        case 0:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next2[i][j]=type0[i][j];
                }
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next2[i][j]=type1[i][j];
                }
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next2[i][j]=type2[i][j];
                }
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next2[i][j]=type3[i][j];
                }
            }
            break;
        case 4:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next2[i][j]=type4[i][j];
                }
            }
            break;
        case 5:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next2[i][j]=type5[i][j];
                }
            }
            break;
        case 6:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {

                    next2[i][j]=type6[i][j];
                }
            }
            break;
    }
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
    //LCD_ShowNum(20, 20, (sum2 - sum), 4, 12);
    if (sum2 - sum != 4) {
        return 1;
    } else {
        delete(x, y, type);
    }
    return 0;
}
/*
 * 将当前位??(x,y)的形状写入container
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
 * 将停止的形状方块写入static_container
 */
void record2(int x, int y, int type[][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (type[i][j] == 1 && x + i < 31 && y + j < 20 && x + i >= 0
                && y + j >= 0) {
                static_container[x + i][y + j] = 1;
            }
        }
    }
}
/*
 * 将颜色信息记录下来
 */
void recordColor(int x, int y, int type[][4],uint16_t col) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (type[i][j] == 1 && x + i < 31 && y + j < 20 && x + i >= 0
                && y + j >= 0) {
                colorContainer[x + i][y + j] = col;
            }
        }
    }
}
/*
 * 将container位置(x,y)的形状删??
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
 * 将方块向下移??
 * 返回值表示有没有走到底，0表示到底了，1表示还没??
 */
int moveDown(int x, int y, int type[][4], uint16_t color) {
    if (BcheckCrash(x, y, type, 0) == 0) {
        clearPlane(x, y, type);
        drawPlane(x + 1, y, type, color);
        return 1;
    } else {
        return 0;
    }
}
void deleteLine(int x){
    for(int i=0;i<4;i++){
        if(x+i<31){
            int full = 1;
            for(int j = 0;j<20;j++){
                if(static_container[x+i][j]==0){
                    full = 0;
                }
            }
            if(full == 1){
                executeDelete(x+i);
            }
        }
    }
}
void executeDelete(int x){
    for(int j=0;j<20;j++){
        ClearPoint(j,x);
        container[x][j] = 0;
        static_container[x][j] = 0;
    }
    user_score+=30;
    //LCD_ShowNum(183, 145, user_score, 4, 12);
    //LCD_ShowNum(100, 200, user_score, 4, 12);
    for(int i = x-1;i>=0;i--){
        for(int j=0;j<20;j++){
            if(static_container[i][j]==1){
                ClearPoint(j,i);
                uint16_t col = colorContainer[i][j];
                container[i][j] = 0;
                static_container[i][j] = 0;
                DrawPoint(j,i+1,col);
                container[i+1][j] = 1;
                static_container[i+1][j] = 1;
                colorContainer[i+1][j] = col;
            }
        }
    }
    if(user_score>=user_level*user_level*30*1){
        user_level++;
        LCD_ShowString(35, 80, 200, 12, 24, (uint8_t*) "Level Up!");
        HAL_Delay(100);
        LCD_Fill(35,80,140,104,WHITE);
        //LCD_ShowString(100, 180, 200, 12, 24, (uint8_t*) "level");

        user_delay--;
    }
}
int moveRight(int x, int y, int type[][4], uint16_t color) {
    if (BcheckCrash(x, y, type, 2) == 0) {
        clearPlane(x, y, type);
        drawPlane(x, y+1, type, color);
        return 1;
    } else {
        return 0;
    }
}


int moveLeft(int x, int y, int type[][4], uint16_t color) {
    if (BcheckCrash(x, y, type, 1) == 0) {
        clearPlane(x, y, type);
        drawPlane(x , y-1, type, color);
        return 1;
    } else {
        return 0;
    }
}



/*
 * ??查碰撞，direction是行动方向，0 = down??1 = left??2 = right
 * 有碰撞则返回1，无则返??0
 */
int checkCrash(int x, int y, int type[][4], int direction) {
    int sum = 0;
    uint16_t container_tmp[31][20];
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 20; j++) {
            container_tmp[i][j] = container[i][j];
        }
    }
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



int BcheckCrash(int x, int y, int type[][4], int direction) {
    int sum = 0;
    uint16_t container_tmp[31][20];
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 20; j++) {
            container_tmp[i][j] = container[i][j];
            sum+=container_tmp[i][j];
        }
    }

    switch (direction) {
        case 0://down

            //delete

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (type[i][j] == 1 && x + i < 31 && y + j < 20 && x + i >= 0
                        && y + j >= 0) {
                        container_tmp[x + i][y + j] = 0;
                    }
                }
            }

            //record


            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (type[i][j] == 1 && x+1 + i < 31 && y + j < 20 && x+1 + i >= 0
                        && y + j >= 0) {
                        container_tmp[x+1 + i][y + j] = 1;
                    }
                }
            }

            //delete(x, y, type);
            //record(x + 1, y, type);
            for (int i = 0; i < 31; i++) {
                for (int j = 0; j < 20; j++) {
                    sum -= container_tmp[i][j];
                }
            }
            if (sum == 0) {
                delete(x,y,type);
                record(x+1,y,type);
                return 0;
            } else {
                //delete(x + 1, y, type);
                //record(x, y, type);
                return 1;
            }
            break;
        case 1:	//left


            //delete
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (type[i][j] == 1 && x + i < 31 && y + j < 20 && x + i >= 0
                        && y + j >= 0) {
                        container_tmp[x + i][y + j] = 0;
                    }
                }
            }

            //record

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (type[i][j] == 1 && x + i < 31 && y-1 + j < 20 && x + i >= 0
                        && y-1 + j >= 0) {
                        container_tmp[x + i][y-1 + j] = 1;
                    }
                }
            }


            for (int i = 0; i < 31; i++) {
                for (int j = 0; j < 20; j++) {
                    sum -= container_tmp[i][j];
                }
            }
            if (sum == 0) {
                delete(x,y,type);
                record(x,y-1,type);
                return 0;
            } else {

                return 1;
            }
            break;


        case 2:	//right



            //delete
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (type[i][j] == 1 && x + i < 31 && y + j < 20 && x + i >= 0
                        && y + j >= 0) {
                        container_tmp[x + i][y + j] = 0;
                    }
                }
            }

            //record
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (type[i][j] == 1 && x + i < 31 && y+1 + j < 20 && x + i >= 0
                        && y+1 + j >= 0) {
                        container_tmp[x + i][y+1 + j] = 1;
                    }
                }
            }


            for (int i = 0; i < 31; i++) {
                for (int j = 0; j < 20; j++) {
                    sum -= container_tmp[i][j];
                }
            }
            if (sum == 0) {
                delete(x,y,type);
                record(x,y+1,type);
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
//    LCD_Set_Window(0,0,250,300);
    LCD_DrawRectangle(0, 248, 160, 253);
    LCD_DrawRectangle(160, 0, 165, 253);
    LCD_Color_Fill(160,0,165,253,BLUE);
    LCD_Color_Fill(0,248,160,253,BLUE);
    LCD_DrawLine(160, 248, 165, 248);
    LCD_Draw_Circle(200,27,25);
    //LCD_ShowString(190, 55, 200, 12, 12, (uint8_t*) "next");
    LCD_Draw_Circle(200,80,25);
    LCD_ShowString(190, 108, 200, 12, 12, (uint8_t*) "next");
    LCD_DrawRectangle(165, 125, 243, 175);
    LCD_Color_Fill(165,125,243,135,BLUE);
    LCD_ShowString(185, 135, 200, 12, 12, (uint8_t*) "score");
    LCD_ShowNum(183, 145, user_score, 4, 12);
    LCD_Color_Fill(165,165,243,175,BLUE);
    LCD_ShowString(185, 180, 200, 12, 12, (uint8_t*) "level");
    LCD_ShowNum(183,200,user_level,4,12);


}
/*
 * 在画布的位置(x,y)加入有形状的方块??
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
 * 在画布的位置(x,y)擦除方块??
 */
void clearPlane(int x, int y, int array[][4]) {
//	LCD_ShowNum(31, 40,array[0][0],2, 24);
    for (uint16_t i = 0; i < 4; i++) {
        for (uint16_t j = 0; j < 4; j++) {
            if (array[i][j] == 1) {
                ClearPoint(y + j, x + i);
                if (y+j>0 && static_container[x+i][y+j-1]==1){
                    DrawPoint(y+j-1,x+i,colorContainer[x+i][y+j-1]);
                }
                if (y+j+1<31 && static_container[x+i][y+j+1]==1){
                    DrawPoint(y+j+1,x+i,colorContainer[x+i][y+j+1]);
                }
            }
        }
    }
    InitialPlane();
}
/*
 * 像素放大，每??个方块是8*8像素点的集合??
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
 * 将方块擦??
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

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    //HAL_Delay(100);
    switch (GPIO_Pin) {
        case KEY_WK_Pin://left
            if (HAL_GPIO_ReadPin(KEY_WK_GPIO_Port, KEY_WK_Pin) == GPIO_PIN_SET) {
                HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
                HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
                direction_type=1;

            } break;

        case KEY1_Pin://rotate
            if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET) {
                HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
                direction_type=3;
            }
            break;

        case KEY0_Pin://right
            if (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET) {
                HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
                direction_type=2;
            }
            break;

        default:
            direction_type=0;
            break;}
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

