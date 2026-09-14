#include "stm32f4xx.h"

int main(void)
{
    /* GPIOD: PD12..PD15 sebagai output, LED dimatikan. */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER &= ~(0xFFU << 24);
    GPIOD->MODER |=  (0x55U << 24);
    GPIOD->BSRR = (0xFU << (12 + 16));

    /* GPIOA: PA0 sebagai masukan (nilai reset MODER = 0). */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* Aktifkan clock SYSCFG (diperlukan untuk menghubungkan EXTI ke pin). */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    /* Hubungkan EXTI0 ke PA0 (EXTICR[0] = 0b0000 -> Port A). */
    SYSCFG->EXTICR[0] &= ~(0xFU << 0);

    /* EXTI0: picu pada sisi naik (rising), buka mask. */
    EXTI->IMR  |= (1U << 0);
    EXTI->RTSR |= (1U << 0);

    /* Aktifkan interupsi EXTI0 pada NVIC. */
    NVIC_SetPriority(EXTI0_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_IRQn);

    while (1)
    {
    }
}

/* Interrupt EXTI0: tombol PA0 ditekan -> toggle LED PD12..PD15. */
void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & (1U << 0))
    {
        EXTI->PR = (1U << 0);          /* bersihkan pending */
        GPIOD->ODR ^= (0xFU << 12);    /* toggle semua LED   */
    }
}
