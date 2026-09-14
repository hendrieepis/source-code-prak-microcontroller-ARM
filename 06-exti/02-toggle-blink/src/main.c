#include "stm32f4xx.h"

/* Penanda apakah blinky aktif (diubah di dalam interrupt). */
static volatile uint8_t g_blink = 0;

static void delay(uint32_t n)
{
    while (n--) {}
}

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER &= ~(0xFFU << 24);
    GPIOD->MODER |=  (0x55U << 24);
    GPIOD->BSRR = (0xFU << (12 + 16));

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTICR[0] &= ~(0xFU << 0);

    EXTI->IMR  |= (1U << 0);
    EXTI->RTSR |= (1U << 0);

    NVIC_SetPriority(EXTI0_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_IRQn);

    while (1)
    {
        if (g_blink)
        {
            GPIOD->ODR ^= (1U << 12);   /* kedipkan LD4 */
            delay(0xFFFFF);
        }
        else
        {
            GPIOD->BSRR = (1U << (12 + 16)); /* matikan LD4 */
        }
    }
}

/* Setiap tombol ditekan, aktif/nonaktifkan blinky. */
void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & (1U << 0))
    {
        EXTI->PR = (1U << 0);
        g_blink ^= 1;
    }
}
