/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
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
unsigned int SystemTimer = 0;

#define RXBUFFERSIZE 256     //
char RxBuffer[RXBUFFERSIZE]; //
uint8_t aRxBuffer;           //
uint8_t Uart1_Rx_Cnt = 0;    //

#define USART3_MAX_RECV_LEN 256
char USART3_RX_BUF[USART3_MAX_RECV_LEN];
uint8_t Uart2_aRxBuffer;

#define lenth 16

#define  R_NUM               8     //接收缓冲区个数
#define  RBUFF_UNIT          300   //接收缓冲区长度
unsigned char  MQTT_RxDataBuf[R_NUM][RBUFF_UNIT];           //数据的接收缓冲区,所有服务器发来的数据，存放在该缓冲区,缓冲区第一个字节存放数据长度
unsigned char *MQTT_RxDataInPtr;                            //指向接收缓冲区存放数据的位置
unsigned char *MQTT_RxDataOutPtr;                           //指向接收缓冲区读取数据的位置
unsigned char *MQTT_RxDataEndPtr;                           //指向接收缓冲区结束的位置

char fina_data1[5];
char fina_data2[5];
int finaldata1;
int finaldata2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
    MX_DMA_Init();
    MX_TIM2_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    /* USER CODE BEGIN 2 */
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_UART_Receive_DMA(&huart2, (uint8_t *)USART3_RX_BUF, lenth);

    static uint8_t seri_count = 0;
    char check_flag, end_flag, j, k = 0;
    uint8_t x;
    // static uint8_t uflag = 0;
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        // printf("a\r\n");
        // HAL_Delay(1000);
        // if (USART3_RX_BUF[14] == 0x0A) {
        //     for (size_t i = 0; i < seri_count; i++) {
        //         /* code */
        //         // printf("%x ", USART3_RX_BUF[i]);
        //         // HAL_UART_Transmit(&huart1, (uint8_t *)&USART3_RX_BUF[i], 1, 0xFFFF);
        //         // HAL_UART_Transmit(&huart1, (uint8_t *)"step3\r\n", 8, 0xFFFF);
        //         switch (USART3_RX_BUF[i]) {
        //             case 0x6D:
        //                 check_flag = i;
        //                 // u1_printf("0x6D在第%d???", check_flag);
        //                 // HAL_UART_Transmit(&huart1, (uint8_t *)check_flag, 1, 0xFFFF);
        //                 break;
        //             case 0x23:
        //                 end_flag = i;
        //                 // u1_printf("0x0D在第%d???", end_flag);
        //                 // HAL_UART_Transmit(&huart1, (uint8_t *)end_flag, 1, 0xFFFF);
        //                 break;
        //             default:
        //                 break;
        //         }
        //     }

        //     for (size_t i = 2; i < check_flag; i++) {

        //         if (USART3_RX_BUF[i] == 0x2E) {
        //             continue;
        //         }
        //         fina_data1[j++] = USART3_RX_BUF[i];
        //     }
        //     for (size_t a = check_flag + 1; a < end_flag; a++) {

        //         if (USART3_RX_BUF[a] == 0x2C) {
        //             continue;
        //         }
        //         fina_data2[k++] = USART3_RX_BUF[a];
        //     }

        //     sscanf(fina_data1, "%d", &finaldata1); // 字符串转int
        //     sscanf(fina_data2, "%d", &finaldata2); // 字符串转int

        //     printf("距离=%dmm,回光=%d\r\n", finaldata1, finaldata2); // print用串???2，串???1用来和激光模块???讯
        //     for (x = 0; x < j; x++) {
        //         fina_data1[x] = 0;
        //         fina_data2[x] = 0;
        //     }
        //     // uflag      = 0;
        //     seri_count = 0;
        //     j          = 0;
        //     k          = 0;
        // }
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

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL     = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
/**
 * 函数功能: 重定向c库函数printf到DEBUG_USARTx
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}
/**
 * 函数功能: 重定向c库函数getchar,scanf到DEBUG_USARTx
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
    return ch;
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == (&htim2)) {
        SystemTimer++;
        printf("SystemTimer=%d\r\n", SystemTimer);
        if (SystemTimer >= 121) {
            /* code */
            SystemTimer = 0;
            // OpenTimer   = 0;
        }
        HAL_UART_Transmit_DMA(&huart2, (uint8_t *)"iSM", 3);
    }
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    // static uint8_t seri_count = 0;
    // char check_flag, end_flag, j, k = 0;
    // uint8_t x;
    // static uint8_t uflag = 0;
    /* Prevent unused argument(s) compilation warning */
    // UNUSED(huart);
    /* NOTE: This function Should not be modified, when the callback is needed,
             the HAL_UART_TxCpltCallback could be implemented in the user file
     */
    if (huart->Instance == USART1) {
        char a[] = "distance_saze";
        if (Uart1_Rx_Cnt >= 255) // 溢出判断
        {
            Uart1_Rx_Cnt = 0;
            memset(RxBuffer, 0x00, sizeof(RxBuffer));
            HAL_UART_Transmit(&huart1, (uint8_t *)a, strlen(a), 0xFFFF);
        } else {
            RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;

            if ((RxBuffer[Uart1_Rx_Cnt - 1] == 0x0A) && (RxBuffer[Uart1_Rx_Cnt - 2] == 0x0D)) // 判断结束?????????
            {
                HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer, Uart1_Rx_Cnt, 0xFFFF); // 将收到的信息发???出?????????
                while (HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX)
                    ;
                Uart1_Rx_Cnt = 0;
                memset(RxBuffer, 0x00, sizeof(RxBuffer)); // 清空数组
            }
        }
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1); // 再开?????????接收??????????????????
    }
    if (huart->Instance == USART2) {
        /* code */
        // if (Uart2_aRxBuffer == 0x44) {
        //     uflag = 1;
        //     // HAL_UART_Transmit(&huart1, (uint8_t *)"step1", 6, 0xFFFF);
        // }
        // if (uflag) {
        //     USART3_RX_BUF[seri_count++] = Uart2_aRxBuffer;
        //     // HAL_UART_Transmit(&huart1, (uint8_t *)"step2", 6, 0xFFFF);
        //     if (Uart2_aRxBuffer == 0x0A) {
        //         for (size_t i = 0; i < seri_count; i++) {
        //             /* code */
        //             // printf("%x ", USART3_RX_BUF[i]);
        //             // HAL_UART_Transmit(&huart1, (uint8_t *)&USART3_RX_BUF[i], 1, 0xFFFF);
        //             // HAL_UART_Transmit(&huart1, (uint8_t *)"step3\r\n", 8, 0xFFFF);
        //             switch (USART3_RX_BUF[i]) {
        //                 case 0x6D:
        //                     check_flag = i;
        //                     // u1_printf("0x6D在第%d???", check_flag);
        //                     // HAL_UART_Transmit(&huart1, (uint8_t *)check_flag, 1, 0xFFFF);
        //                     break;
        //                 case 0x23:
        //                     end_flag = i;
        //                     // u1_printf("0x0D在第%d???", end_flag);
        //                     // HAL_UART_Transmit(&huart1, (uint8_t *)end_flag, 1, 0xFFFF);
        //                     break;
        //                 default:
        //                     break;
        //             }
        //         }

        //         for (size_t i = 2; i < check_flag; i++) {

        //             if (USART3_RX_BUF[i] == 0x2E) {
        //                 continue;
        //             }
        //             fina_data1[j++] = USART3_RX_BUF[i];
        //         }
        //         for (size_t a = check_flag + 1; a < end_flag; a++) {

        //             if (USART3_RX_BUF[a] == 0x2C) {
        //                 continue;
        //             }
        //             fina_data2[k++] = USART3_RX_BUF[a];
        //         }

        //         sscanf(fina_data1, "%d", &finaldata1); // 字符串转int
        //         sscanf(fina_data2, "%d", &finaldata2); // 字符串转int

        //         printf("距离=%dmm,回光=%d\r\n", finaldata1, finaldata2); // print用串???2，串???1用来和激光模块???讯
        //         for (x = 0; x < j; x++) {
        //             fina_data1[x] = 0;
        //             fina_data2[x] = 0;
        //         }
        //         uflag      = 0;
        //         seri_count = 0;
        //         j          = 0;
        //         k          = 0;
        //     }
        // }
        // HAL_UART_Receive_IT(&huart2, (uint8_t *)&Uart2_aRxBuffer, 1);
        for (size_t i = 0; i < lenth; i++) {
            /* code */
            printf("%x ", USART3_RX_BUF[i]);
        }
        memcpy(&MQTT_RxDataInPtr[0], USART3_RX_BUF, lenth);
        HAL_UART_Receive_DMA(&huart2, (uint8_t *)USART3_RX_BUF, lenth);
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
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
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
