#include <stm32f3xx.h>
#include <cmsis_os.h>

#include <threads.h>
#include <lsm303dlhc.h>

static void SystemClock_Config(void);
static void Error_Handler(void);

extern uint32_t counter;

void Init_Timers(void);

osThreadDef(handlerThread, osPriorityAboveNormal, 1, 0);
osThreadDef(visioThread, osPriorityNormal, 1, 0);
osMutexDef (accelBuffer_mutex);

int main() {
	GPIO_InitTypeDef GPIO_InitDef;
	
	SystemClock_Config();
	SystemCoreClockUpdate();
	
	HAL_Init();
	
	/* driver init */
	lsm303dlhc_init();
	
	osKernelInitialize();
	Init_Timers();
	
	
	handlerThread_id = osThreadCreate(osThread(handlerThread), NULL);
	visioThread_id = osThreadCreate(osThread(visioThread), NULL);
	accelBuffer_mutex_id = osMutexCreate(osMutex(accelBuffer_mutex));
	
	// enable clock for GPIOE
	__HAL_RCC_GPIOE_CLK_ENABLE();

	// init GPIO pin
	GPIO_InitDef.Pin = GPIO_PIN_9;
	GPIO_InitDef.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitDef.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(GPIOE, &GPIO_InitDef);
	
	// set LD3
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	
	osKernelStart();
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV                     = 1
  *            PLLMUL                         = RCC_PLL_MUL9 (9)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}
