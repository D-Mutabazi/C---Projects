/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
volatile uint8_t g_left_button_pressed= 0 ;
volatile uint8_t g_right_button_pressed = 0 ;
volatile uint8_t g_top_button_pressed = 0 ;
volatile uint8_t g_bottom_button_pressed = 0 ;
volatile uint8_t g_middle_button_pressed = 0 ;


volatile uint8_t button_state = 1;  // stable button state
uint32_t ticks_pressed = 0  ;

volatile uint32_t pulse_count = 0 ;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != RESET){


		if(HAL_GetTick() - ticks_pressed >= 20){
			// stable low state
			if(button_state == 1  && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == 0){
				button_state =0 ; // stable low reached
				ticks_pressed = HAL_GetTick() ;

				g_left_button_pressed =1;
			}

			// stable high state
			if(button_state == 0 && HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_8) == 1 ){
				ticks_pressed = HAL_GetTick() ;
				button_state =1 ; // stable high state

			}
		}
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8) ;
	}

	else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != RESET){



		if(HAL_GetTick() - ticks_pressed >= 20){
			// stable low state
			if(button_state == 1  && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == 0){
				button_state =0 ; // stable low reached
				ticks_pressed = HAL_GetTick() ;

				g_top_button_pressed = 1 ;
			}

			// stable high state
			if(button_state == 0 && HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_9) == 1 ){
				ticks_pressed = HAL_GetTick() ;
				button_state =1 ; // stable high state

			}
		}

		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9) ;

	}

	else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != RESET){



		if(HAL_GetTick() - ticks_pressed >= 20){
			// stable low state
			if(button_state == 1  && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0){
				button_state =0 ; // stable low reached
				ticks_pressed = HAL_GetTick() ;

				g_middle_button_pressed =1 ;
			}

			// stable high state
			if(button_state == 0 && HAL_GPIO_ReadPin(GPIOA ,GPIO_PIN_6) == 1 ){
				ticks_pressed = HAL_GetTick() ;
				button_state =1 ; // stable high state

			}
		}


		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6) ;

	}

	else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != RESET){




		if(HAL_GetTick() - ticks_pressed >= 20){
			// stable low state
			if(button_state == 1  && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == 0){
				button_state =0 ; // stable low reached
				ticks_pressed = HAL_GetTick() ;

				g_right_button_pressed = 1 ;
			}

			// stable high state
			if(button_state == 0 && HAL_GPIO_ReadPin(GPIOA ,GPIO_PIN_7) == 1 ){
				ticks_pressed = HAL_GetTick() ;
				button_state =1 ; // stable high state

			}
		}
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7) ;
	}

	else{

		if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != RESET){

			g_bottom_button_pressed = 1 ;

			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7) ;
		}
	}
  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */


	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET){

		if(HAL_GetTick() - ticks_pressed >= 20){
			// stable low state
			if(button_state == 1  && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == 0){
				button_state =0 ; // stable low reached
				ticks_pressed = HAL_GetTick() ;

				g_bottom_button_pressed = 1 ;
			}

			// stable high state
			if(button_state == 0 && HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_13) == 1 ){
				ticks_pressed = HAL_GetTick() ;
				button_state =1 ; // stable high state

			}
		}

		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13) ;
	}

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
