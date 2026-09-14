#include "stm32f4xx.h"

static void gpio_pwm_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    /* PD12 -> alternate function. */
    GPIOD->MODER &= ~(3U << (12 * 2));
    GPIOD->MODER |=  (2U << (12 * 2));

    /* AF2 (TIM4) untuk PD12. */
    GPIOD->AFR[1] &= ~(0xFU << 16);
    GPIOD->AFR[1] |=  (2U << 16);
}

int main(void)
{
    gpio_pwm_init();

    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    /* Servo: period 20 ms, pulse 1.5 ms.
       tick 10 us -> PSC = 16e6/100e3 - 1 = 159
       period 20 ms -> ARR = 20000us/10us - 1 = 1999
       pulse 1.5 ms -> CCR1 = 1500us/10us = 150 */
    TIM4->PSC = 160 - 1;
    TIM4->ARR = 2000 - 1;

    /* PWM mode 1 pada CH1 + preload. */
    TIM4->CCMR1 = (6U << 4) | (1U << 3);
    TIM4->CCER = (1U << 0);

    TIM4->CCR1 = 150;   /* 1.5 ms (posisi tengah) */

    TIM4->EGR = TIM_EGR_UG;
    TIM4->CR1 |= TIM_CR1_CEN;

    while (1)
    {
    }
}
