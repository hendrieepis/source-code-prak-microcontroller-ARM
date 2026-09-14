#include "stm32f4xx.h"

static volatile uint32_t g_tick = 0;

/* Handler SysTick: mengurangi penghitung setiap 1 ms. */
void SysTick_Handler(void)
{
    if (g_tick > 0)
    {
        g_tick--;
    }
}

/* Delay blokir berbasis SysTick. */
static void delay_ms(uint32_t ms)
{
    g_tick = ms;
    while (g_tick > 0)
    {
    }
}

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    GPIOD->MODER &= ~(0xFFU << 24);
    GPIOD->MODER |=  (0x55U << 24);
    GPIOD->BSRR = (0xFU << (12 + 16));

    SysTick_Config(SystemCoreClock / 1000);   /* tiap 1 ms */

    while (1)
    {
        GPIOD->ODR ^= (0xFU << 12);   /* toggle semua LED */
        delay_ms(10);                 /* tiap 10 ms       */
    }
}
