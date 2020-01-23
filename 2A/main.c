/*
 * ECE 153B - Winter 2020
 *
 * Name(s): Raymond Deng, Abel Semma
 * Section: 7:30pm - 9:50pm
 * Lab: 2A
 */

#include "stm32l476xx.h"
 
void PWM_Init() {
	// Enable GPIO Port E Clock
	RCC->AHB2ENR |= 1<<4;
	
	// Enable TIM1 Clock
	RCC->APB2ENR |= 1<<11;
	
	// Configure PE8
	GPIOE->MODER &= ~GPIO_MODER_MODE8;
	GPIOE->MODER |= GPIO_MODER_MODE8_1;

	GPIOE->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED8;
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED8;

	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD8;
	
	// Configure PWM Output for TIM1 CH 1N

}
 
int main() {
	// Initialization - We will use the default 4 MHz clock
	PWM_Init();
	
	// Periodic Dimming
	int i;
	while(1) {
		// TODO (changing duty cycle, etc.)
		
		for(i=0; i<1000; ++i); // Some Delay
	}
	
	return 0;
}
