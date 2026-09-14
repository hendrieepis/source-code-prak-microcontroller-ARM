#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx.h"

#define PERIPH_BASE           	((uint32_t)0x40000000)
    /*!< Peripheral base address in the alias region */
#define AHB1PERIPH_BASE       	(PERIPH_BASE + 0x00020000)
#define RCC_BASE              	(AHB1PERIPH_BASE + 0x3800)

#define  RCC_AHB1RSTR_GPIODRST  ((uint32_t)0x00000008) //reset GPIOD
#define  RCC_AHB1RSTR_GPIOARST  ((uint32_t)0x00000001) //reset GPIOA

#define  RCC_AHB1Periph_GPIOD   ((uint32_t)0x00000008)  //enable GPIOD
#define  RCC_AHB1ENR_GPIOAEN    ((uint32_t)0x00000001)  //enable GPIOA
#define GPIOD_BASE              (AHB1PERIPH_BASE + 0x0C00)
#define GPIOA_BASE              (AHB1PERIPH_BASE + 0x0000)
#define GPIO_Pin_12             ((uint16_t)0x1000)

int main(void)
{
	// RCC->AHB1RSTR --> reset PORTD
	*((uint32_t volatile *)(RCC_BASE+0x10))=RCC_AHB1RSTR_GPIODRST|RCC_AHB1RSTR_GPIOARST;
	*((uint32_t volatile *)(RCC_BASE+0x10))=0x00; // Exit reset state RCC->AHB1RSTR
	*((uint32_t volatile *)(RCC_BASE+0x30))=RCC_AHB1Periph_GPIOD|RCC_AHB1ENR_GPIOAEN;
	    // RCC->AHB1ENR
	//GPIOD->MODER-> PORTD.(12) Output
	*((uint32_t volatile *)(GPIOD_BASE))|=  (1UL << 2*12) ;
	while(1)
	{
		if ( (*((uint32_t volatile *)(GPIOA_BASE+0x10)) & (1<<0))){
			//GPIOD->BSRR  -->set  PORTD.12
			*((uint32_t volatile *)(0x40020C18))=GPIO_Pin_12;
		} else {
			//GPIOD->BSRR  -->RESET PORTD.12 (bit 12+16)
			*((uint32_t volatile *)(0x40020C18))=0x10000000;
		}
	}
}
