/*
This program outputs a sequence of flashes over a pair of LED's
One LED is attached to PortA bit 0: This we will call the clock bit
The other LED is attached to PortA bit 1: This we will call the data bit
A viewer of the LED's should not the state of the data bit when the clock bit
goes from low (off) to high (on)
The program also includes an "Asynchronous" version of this by driving the 
data LED only.  In this mode it also outputs a start bit and a stop bit on
the data line
*/
#include "stm32l031lib.h"
#define BIT_TIME 100000
void sendData(uint8_t byte);
void sendDataAsync(uint8_t byte);
void clock_high(void);
void clock_low(void);
void data_high(void);
void data_low(void);
int main()
{
	RCC->IOPENR |= 1; // enable GPIOA
	pinMode(GPIOA,0,1); // Make bit 0 an output
	pinMode(GPIOA,1,1); // Make bit 1 an output
	clock_low(); // ensure outputs are low at start
	data_low(); // ensure outputs are low at start
	while(1)
	{
		sendData(0xaa); // transmit some data
		delay(1000000); // wait between bytes
	}
}

void sendData(uint8_t byte)
{
	// This function outputs the data and clock bits
	// in the order LSB to MSB
	int bit_number=0;
	for (bit_number = 0; bit_number < 8; bit_number++)
	{
		// for each bit
		if (byte & 1) // is it high?
		{
			data_high(); // yes, so output high
		}
		else
		{
			data_low();  // no, so output low
		}
		// Now need to put the clock output through a cycle
		clock_high();  
		delay(BIT_TIME);
		clock_low();
		delay(BIT_TIME);
		// Move on to the next bit by shifting the data right one place
		byte = byte >> 1;
	}
}

void sendDataAsync(uint8_t byte)
{
	// This function outputs the data and clock bits
	// in the order LSB to MSB
	int bit_number=0;
	data_high();  // send a start bit
	delay(BIT_TIME); // wait a bit period
	for (bit_number = 0; bit_number < 8; bit_number++)
	{
		// for each bit
		if (byte & 1) // is it high?
		{
			data_high(); // yes, so output high
		}
		else
		{
			data_low();  // no, so output low
		}
		// Wait one bit period
		delay(BIT_TIME);
		// Move on to the next bit by shifting the data right one place
		byte = byte >> 1;
	}
	data_low(); // send a stop bit
	delay(BIT_TIME); // wait one bit period
}
void clock_high()
{
	GPIOA->ODR |= (1u << 0);
}
void clock_low()
{
	GPIOA->ODR &= ~(1u << 0);
}
void data_high()
{
	GPIOA->ODR |= (1u << 1);
}
void data_low()
{
	GPIOA->ODR &= ~(1u << 1);
}
