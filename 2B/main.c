/*
 * ECE 153B - Winter 2020
 *
 * Name(s):
 * Section:
 * Lab: 2B
 */
 
#include "stm32l476xx.h"

#include "LCD.h"
#include "LED.h"
#include "RTC.h"
#include "SysClock.h"

char strTime[12] = {0};
char strDate[12] = {0};

void RTC_Set_Alarm(void) {
	EXTI->RTSR1 |= 1 << 18;
	EXTI->IMR1 |= 1 << 18;
	EXTI->EMR |= 1 << 18;
	EXTI->PR1 |= 1 << 18;
	NVIC_EnableIRQ(RTC_Alarm_IRQn);
	NVIC_SetPriority(RTC_Alarm_IRQn, 0);
}

void RTC_Alarm_Enable(void) {

	//a. Disable both alarms in RTC_CR
	RTC->CR &= ~(ALRMAR);
	RTC->CR &= ~(ALRMBR);


	//b. Remove the RTC write protection
	RTC->WPR |= 0xCA;
	RTC->WPR |= 0x53;



	//c. Clear the alarm enable bit and the interrupt enable bit (??) for both alarms.
	//	 In addition, wait until access to both alarm registers is allowed. (??)
	//   The hardware sets the write flag ALRxWF if alarm x can be modified. (??)
	RTC->ISR &= ~(RTC_ISR_ALRAF);
	RTC->ISR &= ~(RTC_ISR_ALRBF);



	//d. Program Alarm A to set off an alarm when the seconds field of RTC is 30 seconds.
	RTC->ALRMAR &= ~(RTC_ALRMAR_ST);
	RTC->ALRMAR &= ~(RTC_ALRMAR_SU);
	RTC->ALRMAR |= RTC_ALRMAR_ST_1;
	RTC->ALRMAR |= RTC_ALRMAR_ST_2;


	//e. Program Alarm B to set off an alarm every second.
	RTC->ALRMBR &= ~(RTC_ALRMBR_ST);
	RTC->ALRMBR &= ~(RTC_ALRMBR_SU);
	RTC->ALRMBR |= RTC_ALRMBR_SU_0;



	//f. Enable the alarm and its interrupt for both alarm A and alarm B.
	RTC->CR |= RTC_CR_ALRBIE;
	RTC->CR |= RTC_CR_ALRAIE;

	RTC->CR |= RTC_CR_ALRBE;
	RTC->CR |= RTC_CR_ALRAE;


	//g. Enable write protection for the RTC registers.



}

void RTC_Alarm_IRQHandler(void) {
	// TODO
}

int main(void) {	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	LED_Init();
	LCD_Initialization();
	
	RTC_Init();
	RTC_Alarm_Enable();
	RTC_Set_Alarm();
	
	while(1) {
		// TODO
	}
}
