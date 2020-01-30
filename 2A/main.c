/*
 * ECE 153B - Winter 2020
 *
 * Name(s): Raymond Deng, Abel Semma
 * Section: 7:30pm - 9:50pm
 * Lab: 2A
 */
#include <stdio.h>
#include "stm32l476xx.h"
 
void PWM_Init() {
	// Enable GPIO Port E Clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	// Enable TIM1 Clock
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	// Configure PE8
	GPIOE->MODER &= ~GPIO_MODER_MODE8;
	GPIOE->MODER |= GPIO_MODER_MODE8_1;

	GPIOE->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED8;
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED8;

	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD8;
	
	// Configure PWM Output for TIM1 CH 1N
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL8;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL8_0;

	//a: Set direction s.t. timer counts up
	TIM1_CR1 &= ~TIM_CR1_DIR;


	//b: Set the  prescaler value 
	TIM1->PSC=3;


	//c: Set the auto-reload value 
	TIM1->ARR=40000;


	//d: Configure channel 1 to be in output compare mode
	//d(i): Clear output compare mode bits for channel 1
	TIM1_CCMR1 &= ~TIM_CCMR1_OC1M;
	
	//d(ii): Set the output compare mode bits to PWM mode 1 (0110)
	TIM1_CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM1_CCMR1 |= TIM_CCMR1_OC1M_2;
	//d(iii): Enable the output preload for channel 1
	TIM1_CCMR1 |= TIM_CCMR1_OC1PE;



	//e: Set the output polarity for channel 1N to active high
	TIM1_CCER &= ~TIM_CCER_CC1P;



	//f: Enable the output for channel 1N 
	TIM1_CCER |= TIM_CCER_CC1E;


	//g: Enable the main output
	TIM1_BDTR |= TIM_BDTR_MOE;



	//h: Set capture/compare value. 
	TIM1-CCR1 = 20000;

	//i: Enable the counter
	TIM1_CR1 |= TIM_CR1_CEN;

}

void GreenLED_Init(void){

	// Initialize Green LED
	GPIOE->MODER &= ~GPIO_MODER_MODE8;
	GPIOE->MODER |= GPIO_MODER_MODE8_0;
	
	//Configure PB2 output type as Push-Pull
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT8;
	
	//Configure PB2 output type as No Pull-Up, No Pull-Down
	
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD8;
}
void Green_LED_On(void) {
	GPIOE->ODR |= GPIO_ODR_OD8;
}
 
int main() {
	// Initialization - We will use the default 4 MHz clock
	PWM_Init();
	GreenLED_Init();
	
	// Periodic Dimming
	int i;
	while(1) {
		// TODO (changing duty cycle, etc.)
		
		for(i=0; i<20000; 2*i); // Some Delay
		{
			TIM1->CCR1=i;  //when we keep lowering ccr the green LED should become dimmer
		}

	}
	
	return 0;
}
