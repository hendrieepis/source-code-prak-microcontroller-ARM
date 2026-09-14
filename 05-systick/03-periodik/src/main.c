#include "stm32f4xx.h"

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    GPIOD->MODER &= ~(0xFFU << 24);
    GPIOD->MODER |=  (0x55U << 24);
    GPIOD->BSRR = (0xFU << (12 + 16));

    SysTick_Config(SystemCoreClock / 1000);   /* tiap 1 ms */

    while (1)
    {
    }
}

/* Pola: nyala 500 ms, mati 500 ms (periode 1 detik). */
void SysTick_Handler(void)
{
    static uint16_t n = 0;

    if (n < 500)
    {
        GPIOD->BSRR = (0xFU << 12);            /* nyalakan semua */
    }
    else
    {
        GPIOD->BSRR = (0xFU << (12 + 16));     /* matikan semua  */
    }

    n = (n + 1) % 1000;
}
