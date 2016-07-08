#include <stm32f3xx.h>

#include <lsm303dlhc.h>

I2C_HandleTypeDef I2C1_Handle;

/*
 * LSM303DLHC driver's private functions
 */
static void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
static uint8_t lsm303dlhc_read_reg(uint16_t addr, uint8_t reg);
static void lsm303dlhc_write_reg(void);

void lsm303dlhc_init() {
	uint32_t buffer;
	
	/* lowlevel init */
	HAL_I2C_MspInit(&I2C1_Handle);
	
	buffer = lsm303dlhc_read_reg(LINACCEL_I2C_ADDRESS, CTRL_REG1_A);
	buffer = lsm303dlhc_read_reg(GYRO_I2C_ADDRESS, 0x0c);
}

static void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	LINACCEL_GPIO_CLK_ENABLE();
	
	GPIO_InitStructure.Pin = (LSM303DLHC_SCL_PIN | LSM303DLHC_SDA_PIN);
  GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Alternate = LSM303DLHC_GPIO_AF;
  HAL_GPIO_Init(LSM303DLHC_PORT, &GPIO_InitStructure);
	
	hi2c->Instance = LSM303DLHC_I2C;
  hi2c->Init.OwnAddress1 =  LINACCEL_I2C_ADDRESS;
  hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c->Init.OwnAddress2 = 0;
  hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;	
	
	LINACCEL_I2C_CLK_ENABLE();
	
	HAL_I2C_Init(hi2c);
	
}

static uint8_t lsm303dlhc_read_reg(uint16_t addr, uint8_t reg) {
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t value = 0;
	
	status = HAL_I2C_Mem_Read(&I2C1_Handle, addr, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, LSM303DLHC_I2C_TIMEOUT);
	
	return value;
}

static void lsm303dlhc_write_reg(void) {
	
}
