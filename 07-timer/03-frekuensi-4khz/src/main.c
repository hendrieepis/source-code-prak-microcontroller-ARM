#include "stm32f4xx.h"

int main(void)
{
    /* LED PD12 sebagai output. */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER &= ~(3U << (12 * 2));
    GPIOD->MODER |=  (1U << (12 * 2));
    GPIOD->BSRR = (1U << (12 + 16));

    /* Clock TIM2. */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* Target 4 kHz, duty 50%.
       Thigh 125 us -> tick 0.5 us -> PSC = 16e6/2e6 - 1 = 7
       overflow 125 us -> ARR = 125us/0.5us - 1 = 249 */
    TIM2->PSC = 8 - 1;
    TIM2->ARR = 250 - 1;
    TIM2->EGR = TIM_EGR_UG;
    TIM2->SR  = 0;
    TIM2->CR1 |= TIM_CR1_CEN;

    while (1)
    {
        if (TIM2->SR & TIM_SR_UIF)
        {
            TIM2->SR = ~TIM_SR_UIF;
            GPIOD->ODR ^= (1U << 12);   /* toggle PD12 -> 4 kHz */
        }
    }
}
