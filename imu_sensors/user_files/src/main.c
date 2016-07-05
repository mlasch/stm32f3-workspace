#include <stm32f3xx.h>

int main() {
	GPIO_InitTypeDef GPIO_InitDef;
	
	// enable clock for GPIOE
	__HAL_RCC_GPIOE_CLK_ENABLE();

	// init GPIO pin
	GPIO_InitDef.Pin = GPIO_PIN_9;
	GPIO_InitDef.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitDef.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(GPIOE, &GPIO_InitDef);
	
	// generate an interrupt every 1ms
	HAL_SYSTICK_Config(SystemCoreClock/1000);
	
	// set LD3
	//HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	
	while(1) {
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
		HAL_Delay(100);	//delay for 100ms
	}
	
}
