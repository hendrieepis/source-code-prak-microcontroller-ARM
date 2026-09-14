#include "stm32f4xx.h"

static void gpio_pwm_init(void)
{
    /* GPIOD clock. */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    /* PD12..PD15 -> alternate function. */
    GPIOD->MODER &= ~((3U << (12 * 2)) | (3U << (13 * 2)) |
                      (3U << (14 * 2)) | (3U << (15 * 2)));
    GPIOD->MODER |=  ((2U << (12 * 2)) | (2U << (13 * 2)) |
                      (2U << (14 * 2)) | (2U << (15 * 2)));

    /* AF2 (TIM4) untuk PD12..PD15 (AFRH, nibble pin 8..15). */
    GPIOD->AFR[1] &= ~((0xFU << 16) | (0xFU << 20) | (0xFU << 24) | (0xFU << 28));
    GPIOD->AFR[1] |=  ((2U << 16) | (2U << 20) | (2U << 24) | (2U << 28));
}

int main(void)
{
    gpio_pwm_init();

    /* Clock TIM4. */
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    /* 1 kHz: PSC = 79 (tick 5 us), ARR = 199 (period 1 ms). */
    TIM4->PSC = 80 - 1;
    TIM4->ARR = 200 - 1;

    /* PWM mode 1 pada CH1..CH4 + preload enable. */
    TIM4->CCMR1 = (6U << 4) | (1U << 3) | (6U << 12) | (1U << 11);
    TIM4->CCMR2 = (6U << 4) | (1U << 3) | (6U << 12) | (1U << 11);

    /* Aktifkan keluaran CH1..CH4. */
    TIM4->CCER = (1U << 0) | (1U << 4) | (1U << 8) | (1U << 12);

    /* Duty: CH1 25%, CH2 75%, CH3 50%, CH4 80%. */
    TIM4->CCR1 = 200 * 25 / 100;
    TIM4->CCR2 = 200 * 75 / 100;
    TIM4->CCR3 = 200 * 50 / 100;
    TIM4->CCR4 = 200 * 80 / 100;

    TIM4->EGR = TIM_EGR_UG;
    TIM4->CR1 |= TIM_CR1_CEN;

    while (1)
    {
    }
}
