#include <stdint.h>
#include <stm32l031xx.h>
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void delay(volatile uint32_t dly);
void setBit( volatile uint32_t *dest, uint32_t Mask);
void clearBit( volatile uint32_t *dest, uint32_t Mask);
void asm_delay(volatile uint32_t dly);
void asm_setBit( volatile uint32_t *dest, uint32_t Mask);
void asm_clearBit( volatile uint32_t *dest, uint32_t Mask);
int main()
{
	RCC->IOPENR = RCC->IOPENR | (1 << 1); // Enable GPIOB
	pinMode(GPIOB,3,1); // Make GPIOB_3 (LD3) an output
	
	while(1)
	{
		asm_setBit(&GPIOB->ODR,3);
		asm_delay(100000);
		asm_clearBit(&GPIOB->ODR,3);
		asm_delay(100000);
	}
}
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
		Port->PUPDR = Port->PUPDR & ~(3u << BitNumber*2); // clear pull-up resistor bits
		Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); // set pull-up bit
}
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode)
{
	// This function writes the given Mode bits to the appropriate location for
	// the given BitNumber in the Port specified.  It leaves other bits unchanged
	// Mode values:
	// 0 : digital input
	// 1 : digital output
	// 2 : Alternative function
	// 3 : Analog input
	uint32_t mode_value = Port->MODER; // read current value of Mode register 
	Mode = Mode << (2 * BitNumber);    // There are two Mode bits per port bit so need to shift
																	   // the mask for Mode up to the proper location
	mode_value = mode_value & ~(3u << (BitNumber * 2)); // Clear out old mode bits
	mode_value = mode_value | Mode; // set new bits
	Port->MODER = mode_value; // write back to port mode register
}
void delay(volatile uint32_t dly)
{
	while(dly--);
}
void setBit( volatile uint32_t *dest, uint32_t Mask)
{
	*dest = *dest | (1u << Mask);
}
void clearBit( volatile uint32_t  *dest, uint32_t Mask)
{	
	*dest = *dest & ~(1u << Mask);
}
