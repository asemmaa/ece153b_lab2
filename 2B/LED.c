/*
 * ECE 153B - Winter 2020
 *
 * Name(s):
 * Section:
 * Lab: 1B
 */

#include "LED.h"

void LED_Init(void) {
	// Initialize Red LED
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	
	GPIOB->MODER &= ~GPIO_MODER_MODE2;
	GPIOB->MODER |= GPIO_MODER_MODE2_0;
	
	
	//Configure PB2 output type as Push-Pull
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT2;
	
	//Configure PB2 output type as No Pull-Up, No Pull-Down
	
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD2;
	
	
	
	// Initialize Green LED
	GPIOE->MODER &= ~GPIO_MODER_MODE8;
	GPIOE->MODER |= GPIO_MODER_MODE8_0;
	
	//Configure PB2 output type as Push-Pull
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT8;
	
	//Configure PB2 output type as No Pull-Up, No Pull-Down
	
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD8;
}

void Red_LED_Off(void) {
	GPIOB->ODR &= ~GPIO_ODR_OD2;
}

void Red_LED_On(void) {
	GPIOB->ODR |= GPIO_ODR_OD2;
}

void Red_LED_Toggle(void){
	GPIOB->ODR ^= GPIO_ODR_OD2;
}

void Green_LED_Off(void) {
	GPIOE->ODR &= ~GPIO_ODR_OD8;
}

void Green_LED_On(void) {
	GPIOE->ODR |= GPIO_ODR_OD8;
}

void Green_LED_Toggle(void) {
	GPIOE->ODR ^= GPIO_ODR_OD8;
}
