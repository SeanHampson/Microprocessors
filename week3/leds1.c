#include <stdint.h>
#include <stm32l031xx.h>
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);
void delay(volatile uint32_t dly);

void GreenOn(void);
void GreenOff(void);

void YellowOn(void);
void YellowOff(void);

void RedOn(void);
void RedOff(void);

int ButtonPressed(void);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);

int main()
{
    //uint32_t Count=0;
    RCC->IOPENR = 3;   // Turn on GPIOA and GPIOB
    
    pinMode(GPIOB, 4, 0); // Make GPIOB_4 an input
    enablePullUp(GPIOB,4);
    pinMode(GPIOA, 0, 1); // Make GPIOA_0 an output
    pinMode(GPIOA, 1, 1); // Make GPIOA_1 an output
    pinMode(GPIOA, 2, 1); // Make GPIOA_2 an output

	while(1)
	{
		GreenOn();
		while( !ButtonPressed() );
		delay(400000);  // Wait
		GreenOff();
		delay(100000);  // Wait
		YellowOn();
		delay(1000000);  // Wait
		YellowOff();
		delay(100000);  // Wait
		RedOn();
		delay(1500000);  // Wait
		RedOff();
		delay(100000);  // Wait
		
		/* 
		while( !ButtonPressed() );
		// GPIOA->ODR = Count; // Make Bit 3 high (8 = 2^3)
		GreenOn();
		delay(100000);  // Wait
		GreenOff();
		delay(100000);  // Wait
		
		YellowOn();
		delay(100000);  // Wait
		YellowOff();
		delay(100000);  // Wait
		
		RedOn();
		delay(100000);  // Wait
		RedOff();
		delay(100000);  // Wait
		*/
		// Count++;
	}
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

void GreenOn()
{
    // To turn on the green LED need to set bit 0 of PORTA
    // must not affect other bits
    GPIOA->ODR  = GPIOA->ODR | ( 1 << 0 );
}
void GreenOff()
{
    // To turn off the green LED need to clear bit 0 of PORTA
    // must not affect other bits
    GPIOA->ODR  = GPIOA->ODR & ~((unsigned)1 << 0 );
}

void YellowOn()
{
    // To turn on the yellow LED need to set bit 1 of PORTA
    // must not affect other bits
    GPIOA->ODR  = GPIOA->ODR | ( 1 << 1 );
}
void YellowOff()
{
    // To turn off the yellow LED need to clear bit 1 of PORTA
    // must not affect other bits
    GPIOA->ODR  = GPIOA->ODR & ~((unsigned)1 << 1 );
}

void RedOn()
{
    // To turn on the red LED need to set bit 2 of PORTA
    // must not affect other bits
    GPIOA->ODR  = GPIOA->ODR | ( 1 << 2 );
}
void RedOff()
{
    // To turn off the red LED need to clear bit 2 of PORTA
    // must not affect other bits
    GPIOA->ODR  = GPIOA->ODR & ~((unsigned)1 << 2 );
}

int ButtonPressed()
{
		// Return 1 if button pressed, zero otherwise
		if( ( GPIOB->IDR & ( 1 << 4 ) ) == 0 )
		{	// button pressed
				return 1;
		}
		else
		{
				return 0;
		}
}

void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
        Port->PUPDR = Port->PUPDR & ~(3u << BitNumber*2); // clear pull-up resistor bits
        Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); // set pull-up bit
}
