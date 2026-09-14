#include "stm32f4xx.h"

int main(void)
{
    /* Aktifkan clock GPIOD. */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    /* PD12..PD15 sebagai output. */
    GPIOD->MODER &= ~(0xFFU << 24);   /* bersihkan bit 24..31 */
    GPIOD->MODER |=  (0x55U << 24);   /* 01 untuk PD12..PD15  */

    /* Matikan semua LED. */
    GPIOD->BSRR = (0xFU << (12 + 16));

    /* SysTick: interupsi setiap 1 ms. */
    SysTick_Config(SystemCoreClock / 1000);

    while (1)
    {
    }
}

/* Handler SysTick: membalik kondisi PD12..PD15. */
void SysTick_Handler(void)
{
    GPIOD->ODR ^= (0xFU << 12);
}
