#include "stm32f4xx.h"

int main(void)
{
    /* LED PD12 sebagai output. */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER &= ~(3U << (12 * 2));
    GPIOD->MODER |=  (1U << (12 * 2));
    GPIOD->BSRR = (1U << (12 + 16));

    /* Clock TIM2 (APB1). */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* APB1 timer clock = 16 MHz (HSI).
       tick 5 us       -> PSC = 16e6/200e3 - 1 = 79
       overflow 500 us -> ARR = 500us/5us - 1 = 99  */
    TIM2->PSC = 80 - 1;
    TIM2->ARR = 100 - 1;
    TIM2->EGR = TIM_EGR_UG;     /* muat nilai PSC/ARR */
    TIM2->SR  = 0;
    TIM2->CR1 |= TIM_CR1_CEN;   /* jalankan timer */

    while (1)
    {
        if (TIM2->SR & TIM_SR_UIF)
        {
            TIM2->SR = ~TIM_SR_UIF;   /* bersihkan flag update */
            GPIOD->ODR ^= (1U << 12); /* toggle PD12 -> 1 kHz  */
        }
    }
}
