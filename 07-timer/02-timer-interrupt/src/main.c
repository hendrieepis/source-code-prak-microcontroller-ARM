#include "stm32f4xx.h"

int main(void)
{
    /* LED PD12 dan PD13 sebagai output. */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER &= ~((3U << (12 * 2)) | (3U << (13 * 2)));
    GPIOD->MODER |=  ((1U << (12 * 2)) | (1U << (13 * 2)));
    GPIOD->BSRR = (0x3U << (12 + 16));

    /* Clock TIM2. */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* APB1 timer clock = 16 MHz.
       tick 0.5 ms      -> PSC = 16e6/2000 - 1 = 7999
       overflow 0.5 s   -> ARR = 0.5s/0.5ms - 1 = 999  */
    TIM2->PSC = 8000 - 1;
    TIM2->ARR = 1000 - 1;
    TIM2->EGR = TIM_EGR_UG;
    TIM2->SR  = 0;

    TIM2->DIER |= TIM_DIER_UIE;   /* aktifkan interrupt update */
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->CR1 |= TIM_CR1_CEN;

    while (1)
    {
        /* LED PD13 sebagai penanda program utama tetap berjalan. */
        for (volatile int i = 0; i < 1000000; i++) { __asm("nop"); }
        GPIOD->ODR ^= (1U << 13);
    }
}

/* Interrupt timer: toggle PD12 setiap 0.5 s. */
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR = ~TIM_SR_UIF;
        GPIOD->ODR ^= (1U << 12);
    }
}
