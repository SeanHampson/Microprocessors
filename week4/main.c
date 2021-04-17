#include <stdint.h>
#include <stm32l031xx.h>
#include "stm32l031lib.h"

void ADCBegin(void);
uint16_t ADCRead(void);
//Added
void SysTick_Handler(void);

void ADCBegin()
{
	RCC->APB2ENR |= (1u << 9); // Turn on ADC 
	RCC->IOPENR |= 1; // enable GPIOA
	pinMode(GPIOA,4,3); // Make GPIOA_4 an analogue input
	ADC1->CR = 0; // disable ADC before making changes
	ADC1->CR |= (1u << 28); // turn on the voltage regulator
	ADC1->CR |= (1u << 31); // start calibration
	while ( (ADC1->CR & (1u << 31)) != 0); // Wait for calibration to complete.
	ADC1->CHSELR = (1 << 4); // select channel4  
	ADC1->CR |= 1; // enable the ADC
	
}
uint16_t ADCRead(void)
{
	ADC1->CR |= (1 << 2); // start a conversion
	while ( (ADC1->CR & (1 << 2)) != 0); // Wait for conversion to complete.
	return (uint16_t)ADC1->DR;
}
int main()
{
	//Added
	initClock(); // Set the system clock running at 16MHz
	RCC->IOPENR |= 1; // enable GPIOA
	pinMode(GPIOA,0,1); // Make PORTA Bit 0 an output
	//pinMode(GPIOA,1,1); // Make PORTA Bit 1 an output
	//SysTick->LOAD = 15999;   // 16MHz / 16000 = 1kHz
	SysTick->CTRL = 7;       // enable systick counting and interrupts, use core clock
	enable_interrupts();
	
	SerialBegin();
	ADCBegin();
	pinMode(GPIOA,5,1);
	pinMode(GPIOA,1,1);
	GPIOA->ODR |= (1 << 5);
	while(1)
	{
		// Frequency gets affected as the light dims
		SysTick->LOAD = 15999 - (ADCRead()*3);

		//Prints the ADCRead on serial com port
		//for debugging
		printDecimal(ADCRead());
		eputs("\r\n");
		//Set to a number for lighting in my room
		if (ADCRead() < 700)
		{	
			//LED off
			GPIOA->ODR |= 2;
		}
		else
		{
			//LED on
			GPIOA->ODR &= ~2u;
		}
		
		//delay(100000);
	}
}

//Added
void SysTick_Handler(void)
{
	static int ms_counter = 0;
	GPIOA->ODR ^= 1; // Toggle Port A bit 0
	ms_counter ++;   // another millisecond has passed
	if (ms_counter == 1000) // 1 second passed ?
	{
		ms_counter = 0; // zero millisecond counter
		GPIOA->ODR ^= 2; // toggle LED
	}
}




https://youtu.be/c318zLPbgiI

https://youtu.be/K-6g85PlEBM