/* USER CODE BEGIN Header */


/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

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
DAC_HandleTypeDef hdac1;

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_DAC1_Init(void);
/* USER CODE BEGIN PFP */
void Delay_u ( unsigned int T);
void BGT24MTR_reg(void);
void TEST(void);
void LMX2491_Soft_reset(void);
void LMX2491_write_reg (uint8_t value,uint8_t value1,uint8_t value2);
void LMX2491_singleTone(void);
void LMX2491_Saw(void);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



void BGT24MTR_reg_init(void)
{	
	uint16_t BGT_data1 = 0x5800;

	HAL_GPIO_WritePin(GPIOB, CS_bgt_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LE_pll_Pin, GPIO_PIN_SET);
	Delay_u(1000);

	//HAL_SPI_Transmit(&hspi1,(uint8_t*)&BGT_data1,sizeof(BGT_data2),100);
	HAL_SPI_Transmit(&hspi1,(uint8_t*)&BGT_data1,sizeof(BGT_data1),100);
	Delay_u(1000);
	HAL_GPIO_WritePin(GPIOB, CS_bgt_Pin, GPIO_PIN_SET);
}
void TEST(void)
{
	HAL_GPIO_WritePin(GPIOA, pll_MOD_Pin, GPIO_PIN_SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(GPIOA, pll_MOD_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}
void LMX2491_Soft_reset(void) // reset all registers in PLL
{
	uint8_t Data_reset1 = 0x00;
	uint8_t Data_reset2 = 0x02;
	uint8_t Data_reset3 = 0x05;
	HAL_GPIO_WritePin(GPIOB, LE_pll_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, CS_bgt_Pin, GPIO_PIN_SET);
	Delay_u(10);
	HAL_SPI_Transmit(&hspi1,(uint8_t*)&Data_reset1,sizeof(Data_reset1),1000);
	Delay_u(10);
	HAL_SPI_Transmit(&hspi1,(uint8_t*)&Data_reset2,sizeof(Data_reset2),1000);
	Delay_u(10);
	HAL_SPI_Transmit(&hspi1,(uint8_t*)&Data_reset3,sizeof(Data_reset3),1000);
	Delay_u(10);
	HAL_GPIO_WritePin(GPIOB, LE_pll_Pin, GPIO_PIN_SET);
}



/*void delay_us (uint16_t us)   // delay_um using tim2
{
	__HAL_TIM_SET_COUNTER(&htim2,0);  
	while (__HAL_TIM_GET_COUNTER(&htim2) < us);  
}*/

void Delay_u ( unsigned int T) // delay_um without tim2
{
	T=T;
	while (T) {--T;}
}

void LMX2491_write_reg (uint8_t value,uint8_t value1,uint8_t value2) // write reg function to LMX2491
{
	value = value;
	value1 = value1;
	value2 = value2;
	HAL_GPIO_WritePin(GPIOB, LE_pll_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, CS_bgt_Pin, GPIO_PIN_SET);
	Delay_u(100);
	HAL_SPI_Transmit(&hspi1,(uint8_t*)&value,sizeof(value),100);
	Delay_u(100);
	HAL_SPI_Transmit(&hspi1,(uint8_t*)&value1,sizeof(value1),100);
	Delay_u(100);
	HAL_SPI_Transmit(&hspi1,(uint8_t*)&value2,sizeof(value2),100);
	Delay_u(100);
	HAL_GPIO_WritePin(GPIOB, LE_pll_Pin, GPIO_PIN_SET);	 
	Delay_u(1000);
}
void LMX2491_singleTone(void)     // this functions for check PLL spurs
{
		
    LMX2491_write_reg(0x00,0x8D,0x00);   
    LMX2491_write_reg(0x00,0x8C,0x13);   
    LMX2491_write_reg(0x00,0x8B,0x88);   
    LMX2491_write_reg(0x00,0x8A,0x00);   
    LMX2491_write_reg(0x00,0x89,0x00);   
    LMX2491_write_reg(0x00,0x88,0x00);   
    LMX2491_write_reg(0x00,0x87,0x00);   
    LMX2491_write_reg(0x00,0x86,0x00);   
    LMX2491_write_reg(0x00,0x85,0x13);   
    LMX2491_write_reg(0x00,0x84,0x88);   
    LMX2491_write_reg(0x00,0x83,0x00);   
    LMX2491_write_reg(0x00,0x82,0x00);   
    LMX2491_write_reg(0x00,0x81,0x00);   
    LMX2491_write_reg(0x00,0x80,0x00);   
    LMX2491_write_reg(0x00,0x7F,0x00);   
    LMX2491_write_reg(0x00,0x7E,0x13);   
    LMX2491_write_reg(0x00,0x7D,0x88);   
    LMX2491_write_reg(0x00,0x7C,0x00);   
    LMX2491_write_reg(0x00,0x7B,0x00);   
    LMX2491_write_reg(0x00,0x7A,0x00);   
    LMX2491_write_reg(0x00,0x79,0x00);   
    LMX2491_write_reg(0x00,0x78,0x00);   
    LMX2491_write_reg(0x00,0x77,0x13);   
    LMX2491_write_reg(0x00,0x76,0x88);   
    LMX2491_write_reg(0x00,0x75,0x00);   
    LMX2491_write_reg(0x00,0x74,0x00);   
    LMX2491_write_reg(0x00,0x73,0x00);   
    LMX2491_write_reg(0x00,0x72,0x00);   
    LMX2491_write_reg(0x00,0x71,0x00);   
    LMX2491_write_reg(0x00,0x70,0xFF);   
    LMX2491_write_reg(0x00,0x6F,0xFF);   
    LMX2491_write_reg(0x00,0x6E,0x3F);   
    LMX2491_write_reg(0x00,0x6D,0xFF);   
    LMX2491_write_reg(0x00,0x6C,0xFF);   
    LMX2491_write_reg(0x00,0x6B,0x00);   
    LMX2491_write_reg(0x00,0x6A,0x00);   
    LMX2491_write_reg(0x00,0x69,0xFF);   
    LMX2491_write_reg(0x00,0x68,0xFF);   
    LMX2491_write_reg(0x00,0x67,0x00);   
    LMX2491_write_reg(0x00,0x66,0x00);   
    LMX2491_write_reg(0x00,0x65,0x01);   
    LMX2491_write_reg(0x00,0x64,0x00);  
    LMX2491_write_reg(0x00,0x63,0x00);   
    LMX2491_write_reg(0x00,0x62,0xC3);   
    LMX2491_write_reg(0x00,0x61,0x50);   
    LMX2491_write_reg(0x00,0x60,0x3F);  
    LMX2491_write_reg(0x00,0x5F,0xFF);   
    LMX2491_write_reg(0x00,0x5E,0xFF);  
    LMX2491_write_reg(0x00,0x5D,0x7A);   
    LMX2491_write_reg(0x00,0x5C,0x20);   
    LMX2491_write_reg(0x00,0x5B,0xC3);   
    LMX2491_write_reg(0x00,0x5A,0x50);   
    LMX2491_write_reg(0x00,0x59,0x00);   
    LMX2491_write_reg(0x00,0x58,0x00);   
    LMX2491_write_reg(0x00,0x57,0x00);   
    LMX2491_write_reg(0x00,0x56,0x86);   
    LMX2491_write_reg(0x00,0x55,0x00);   
    LMX2491_write_reg(0x00,0x54,0x00);   
    LMX2491_write_reg(0x00,0x53,0x00);   
    LMX2491_write_reg(0x00,0x52,0x01);   
    LMX2491_write_reg(0x00,0x51,0x00);   
    LMX2491_write_reg(0x00,0x50,0x00);   
    LMX2491_write_reg(0x00,0x4F,0x00);  
    LMX2491_write_reg(0x00,0x4E,0xFF);   
    LMX2491_write_reg(0x00,0x4D,0x00);   
    LMX2491_write_reg(0x00,0x4C,0x00);   
    LMX2491_write_reg(0x00,0x4B,0x00);   
    LMX2491_write_reg(0x00,0x4A,0x00);   
    LMX2491_write_reg(0x00,0x49,0x00);   
    LMX2491_write_reg(0x00,0x48,0x00);   
    LMX2491_write_reg(0x00,0x47,0x00);   
    LMX2491_write_reg(0x00,0x46,0x08);   
    LMX2491_write_reg(0x00,0x45,0x01);   
    LMX2491_write_reg(0x00,0x44,0x00);   
    LMX2491_write_reg(0x00,0x43,0x00);   
    LMX2491_write_reg(0x00,0x42,0x00);   
    LMX2491_write_reg(0x00,0x41,0x00);   
    LMX2491_write_reg(0x00,0x40,0x03);   
    LMX2491_write_reg(0x00,0x3F,0x00);   
    LMX2491_write_reg(0x00,0x3E,0x00);   
    LMX2491_write_reg(0x00,0x3D,0x00);   
    LMX2491_write_reg(0x00,0x3C,0x00);   
    LMX2491_write_reg(0x00,0x3B,0x00);   
    LMX2491_write_reg(0x00,0x3A,0x00);   
    LMX2491_write_reg(0x00,0x39,0x00);   
    LMX2491_write_reg(0x00,0x2D,0x00);   
    LMX2491_write_reg(0x00,0x2C,0x00);   
    LMX2491_write_reg(0x00,0x2B,0x00);   
    LMX2491_write_reg(0x00,0x2A,0x00);   
    LMX2491_write_reg(0x00,0x29,0x00);   
    LMX2491_write_reg(0x00,0x28,0x00);   
    LMX2491_write_reg(0x00,0x27,0x52);   
    LMX2491_write_reg(0x00,0x26,0x42);   
    LMX2491_write_reg(0x00,0x25,0x92);   
    LMX2491_write_reg(0x00,0x24,0x4A);   
    LMX2491_write_reg(0x00,0x23,0x41);   
    LMX2491_write_reg(0x00,0x22,0x04);   
	LMX2491_write_reg(0x00,0x21,0x20); 
	LMX2491_write_reg(0x00,0x20,0x00); 
	LMX2491_write_reg(0x00,0x1F,0x2A); 
	LMX2491_write_reg(0x00,0x1E,0x06); 
	LMX2491_write_reg(0x00,0x1D,0x00);
	LMX2491_write_reg(0x00,0x1C,0x1F);
	LMX2491_write_reg(0x00,0x1B,0x08);   
	LMX2491_write_reg(0x00,0x1A,0x00);
	LMX2491_write_reg(0x00,0x19,0x02);
	LMX2491_write_reg(0x00,0x18,0x00);
	LMX2491_write_reg(0x00,0x17,0x01);
	LMX2491_write_reg(0x00,0x16,0xF4);
	LMX2491_write_reg(0x00,0x15,0x00);
	LMX2491_write_reg(0x00,0x14,0x00);
	LMX2491_write_reg(0x00,0x13,0x00);
	LMX2491_write_reg(0x00,0x12,0x2C); 
	LMX2491_write_reg(0x00,0x11,0x00);
	LMX2491_write_reg(0x00,0x10,0x1E); 
	LMX2491_write_reg(0x00,0x0F,0x00);
	LMX2491_write_reg(0x00,0x0E,0x00);
	LMX2491_write_reg(0x00,0x0D,0x00);
	LMX2491_write_reg(0x00,0x0C,0x00);
	LMX2491_write_reg(0x00,0x0B,0x00);
	LMX2491_write_reg(0x00,0x0A,0x00);
    LMX2491_write_reg(0x00,0x09,0x00);
	LMX2491_write_reg(0x00,0x08,0x00);
	LMX2491_write_reg(0x00,0x07,0x00);
	LMX2491_write_reg(0x00,0x06,0x00);
	LMX2491_write_reg(0x00,0x05,0x00);
	LMX2491_write_reg(0x00,0x04,0x00);
	LMX2491_write_reg(0x00,0x03,0x00);
	LMX2491_write_reg(0x00,0x02,0x01);
	LMX2491_write_reg(0x00,0x01,0x00);
	LMX2491_write_reg(0x00,0x00,0x18);
	Delay_u(1000);
}

						
void LMX2491_Saw(void)     // functions for Saw with frame period 40.96 which start  on strob impulse
{
		
    LMX2491_write_reg(0x00,0x8D,0x00);   
    LMX2491_write_reg(0x00,0x8C,0x00);
    LMX2491_write_reg(0x00,0x8B,0xC8);   
    LMX2491_write_reg(0x00,0x8A,0x00);   
    LMX2491_write_reg(0x00,0x89,0x00);   
    LMX2491_write_reg(0x00,0x88,0x00);   
    LMX2491_write_reg(0x00,0x87,0x00);   
    LMX2491_write_reg(0x00,0x86,0x00);   
    LMX2491_write_reg(0x00,0x85,0x00);   
    LMX2491_write_reg(0x00,0x84,0xC8);   
    LMX2491_write_reg(0x00,0x83,0x00);   
    LMX2491_write_reg(0x00,0x82,0x00);   
    LMX2491_write_reg(0x00,0x81,0x00);   
    LMX2491_write_reg(0x00,0x80,0x00);   
    LMX2491_write_reg(0x00,0x7F,0x00);   
    LMX2491_write_reg(0x00,0x7E,0x00);   
    LMX2491_write_reg(0x00,0x7D,0xC8);   
    LMX2491_write_reg(0x00,0x7C,0x00);   
    LMX2491_write_reg(0x00,0x7B,0x00);   
    LMX2491_write_reg(0x00,0x7A,0x00);   
    LMX2491_write_reg(0x00,0x79,0x00);   
    LMX2491_write_reg(0x00,0x78,0x00);   
    LMX2491_write_reg(0x00,0x77,0x50);   
    LMX2491_write_reg(0x00,0x76,0x00);   
    LMX2491_write_reg(0x00,0x75,0x3F);   
    LMX2491_write_reg(0x00,0x74,0xFF);   
    LMX2491_write_reg(0x00,0x73,0xF0);   
    LMX2491_write_reg(0x00,0x72,0x66);   
    LMX2491_write_reg(0x00,0x71,0x80);   
    LMX2491_write_reg(0x00,0x70,0x50);   
    LMX2491_write_reg(0x00,0x6F,0x00);   
    LMX2491_write_reg(0x00,0x6E,0x00);   
    LMX2491_write_reg(0x00,0x6D,0x00);   
    LMX2491_write_reg(0x00,0x6C,0x0F);   
    LMX2491_write_reg(0x00,0x6B,0x9A);   
    LMX2491_write_reg(0x00,0x6A,0x62);   
    LMX2491_write_reg(0x00,0x69,0x50);   
    LMX2491_write_reg(0x00,0x68,0x00);   
    LMX2491_write_reg(0x00,0x67,0x3F);   
    LMX2491_write_reg(0x00,0x66,0xFF);   
    LMX2491_write_reg(0x00,0x65,0xEB);   
    LMX2491_write_reg(0x00,0x64,0x33);  
    LMX2491_write_reg(0x00,0x63,0x40);   
    LMX2491_write_reg(0x00,0x62,0x50);   
    LMX2491_write_reg(0x00,0x61,0x00);   
    LMX2491_write_reg(0x00,0x60,0x00);  
    LMX2491_write_reg(0x00,0x5F,0x00);   
    LMX2491_write_reg(0x00,0x5E,0x14);  
    LMX2491_write_reg(0x00,0x5D,0xCD);   
    LMX2491_write_reg(0x00,0x5C,0x2D);   
    LMX2491_write_reg(0x00,0x5B,0x50);   
    LMX2491_write_reg(0x00,0x5A,0x00);   
    LMX2491_write_reg(0x00,0x59,0x00);   
    LMX2491_write_reg(0x00,0x58,0x00);   
    LMX2491_write_reg(0x00,0x57,0x00);   
    LMX2491_write_reg(0x00,0x56,0x00);   
    LMX2491_write_reg(0x00,0x55,0x00);   
    LMX2491_write_reg(0x00,0x54,0x00);   
    LMX2491_write_reg(0x00,0x53,0x00);   
    LMX2491_write_reg(0x00,0x52,0x18);   
    LMX2491_write_reg(0x00,0x51,0x00);   
    LMX2491_write_reg(0x00,0x50,0x00);   
    LMX2491_write_reg(0x00,0x4F,0x00);  
    LMX2491_write_reg(0x00,0x4E,0xFF);   
    LMX2491_write_reg(0x00,0x4D,0x00);   
    LMX2491_write_reg(0x00,0x4C,0x00);   
    LMX2491_write_reg(0x00,0x4B,0x00);   
    LMX2491_write_reg(0x00,0x4A,0x00);   
    LMX2491_write_reg(0x00,0x49,0x00);   
    LMX2491_write_reg(0x00,0x48,0x00);   
    LMX2491_write_reg(0x00,0x47,0x00);   
    LMX2491_write_reg(0x00,0x46,0x08);   
    LMX2491_write_reg(0x00,0x45,0x01);   
    LMX2491_write_reg(0x00,0x44,0x06);   
    LMX2491_write_reg(0x00,0x43,0x80);   
    LMX2491_write_reg(0x00,0x42,0x00);   
    LMX2491_write_reg(0x00,0x41,0x00);   
    LMX2491_write_reg(0x00,0x40,0x01);   
    LMX2491_write_reg(0x00,0x3F,0x00);   
    LMX2491_write_reg(0x00,0x3E,0x00);   
    LMX2491_write_reg(0x00,0x3D,0x00);   
    LMX2491_write_reg(0x00,0x3C,0x00);   
    LMX2491_write_reg(0x00,0x3B,0x00);   
    LMX2491_write_reg(0x00,0x3A,0x31);   
    LMX2491_write_reg(0x00,0x39,0x00);   
    LMX2491_write_reg(0x00,0x2D,0x00);   
    LMX2491_write_reg(0x00,0x2C,0x00);   
    LMX2491_write_reg(0x00,0x2B,0x00);   
    LMX2491_write_reg(0x00,0x2A,0x00);   
    LMX2491_write_reg(0x00,0x29,0x00);   
    LMX2491_write_reg(0x00,0x28,0x00);   
    LMX2491_write_reg(0x00,0x27,0x52);   
    LMX2491_write_reg(0x00,0x26,0x1F);   
    LMX2491_write_reg(0x00,0x25,0xFA);   
    LMX2491_write_reg(0x00,0x24,0xF2);   
    LMX2491_write_reg(0x00,0x23,0x41);   
    LMX2491_write_reg(0x00,0x22,0xA4);   
	LMX2491_write_reg(0x00,0x21,0x20); 
	LMX2491_write_reg(0x00,0x20,0x00); 
	LMX2491_write_reg(0x00,0x1F,0x2A); 
	LMX2491_write_reg(0x00,0x1E,0x06); 
	LMX2491_write_reg(0x00,0x1D,0x00);
	LMX2491_write_reg(0x00,0x1C,0x1F);
	LMX2491_write_reg(0x00,0x1B,0x08);   
	LMX2491_write_reg(0x00,0x1A,0x00);
	LMX2491_write_reg(0x00,0x19,0x32);
	LMX2491_write_reg(0x00,0x18,0x00);
	LMX2491_write_reg(0x00,0x17,0x00);
	LMX2491_write_reg(0x00,0x16,0x00);
	LMX2491_write_reg(0x00,0x15,0x00);
	LMX2491_write_reg(0x00,0x14,0x00);
	LMX2491_write_reg(0x00,0x13,0x00);
	LMX2491_write_reg(0x00,0x12,0x2C); 
	LMX2491_write_reg(0x00,0x11,0x02);
	LMX2491_write_reg(0x00,0x10,0xEF); 
	LMX2491_write_reg(0x00,0x0F,0x00);
	LMX2491_write_reg(0x00,0x0E,0x00);
	LMX2491_write_reg(0x00,0x0D,0x00);
	LMX2491_write_reg(0x00,0x0C,0x00);
	LMX2491_write_reg(0x00,0x0B,0x00);
	LMX2491_write_reg(0x00,0x0A,0x00);
    LMX2491_write_reg(0x00,0x09,0x00);
	LMX2491_write_reg(0x00,0x08,0x00);
	LMX2491_write_reg(0x00,0x07,0x00);
	LMX2491_write_reg(0x00,0x06,0x00);
	LMX2491_write_reg(0x00,0x05,0x00);
	LMX2491_write_reg(0x00,0x04,0x00);
	LMX2491_write_reg(0x00,0x03,0x00);
	LMX2491_write_reg(0x00,0x02,0x01);
	LMX2491_write_reg(0x00,0x01,0x00);
	LMX2491_write_reg(0x00,0x00,0x18);
	Delay_u(1000);
}



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
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_DAC1_Init();
  /* USER CODE BEGIN 2 */
    LMX2491_Saw();
	HAL_Delay(500);
	SPI1->CR1 &= ~SPI_CR1_SPE;  // disable SPI
	HAL_Delay(500);
	SPI1->CR1 |= SPI_CR1_CPHA;  // reverse cpha
	HAL_Delay(500);
	SPI1->CR1 &= SPI_CR1_SPE;   // enable SPI
	HAL_Delay(500);
	BGT24MTR_reg_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
  while (1)
  {

	//TEST();
			

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_LSI, RCC_MCODIV_1);
}

/**
  * @brief DAC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */
  /** DAC Initialization 
  */
  hdac1.Instance = DAC;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT1 config 
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */

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
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 38400;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, pll_MOD_Pin|Q2_mcu_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, spi_CE_pll_Pin|LE_pll_Pin|CS_bgt_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PF0 PF1 PF6 PF7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : pll_MOD_Pin Q2_mcu_Pin */
  GPIO_InitStruct.Pin = pll_MOD_Pin|Q2_mcu_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA2 PA6 PA12 
                           PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_6|GPIO_PIN_12 
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : spi_CE_pll_Pin LE_pll_Pin CS_bgt_Pin */
  GPIO_InitStruct.Pin = spi_CE_pll_Pin|LE_pll_Pin|CS_bgt_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : MUX_pll_Pin */
  GPIO_InitStruct.Pin = MUX_pll_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MUX_pll_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB11 PB12 PB13 PB14 
                           PB15 PB3 PB4 PB5 
                           PB6 PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5 
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BGT_ANA_Pin */
  GPIO_InitStruct.Pin = BGT_ANA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BGT_ANA_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
