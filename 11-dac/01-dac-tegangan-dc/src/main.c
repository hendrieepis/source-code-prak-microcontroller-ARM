#include "stm32f4xx.h"

static void dac_init(void)
{
    /* Clock DAC (APB1) dan GPIOA. */
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* PA4 sebagai analog (DAC_OUT1). */
    GPIOA->MODER |= (3U << (4 * 2));

    /* Aktifkan kanal 1 DAC (buffer output aktif). */
    DAC->CR |= DAC_CR_EN1;
}

static void delay(uint32_t n)
{
    while (n--) {}
}

int main(void)
{
    dac_init();

    for (;;)
    {
        DAC->DHR12R1 = 0;      /* 0,00 V   */
        delay(0xFFFFF);
        DAC->DHR12R1 = 1024;   /* ~0,82 V  */
        delay(0xFFFFF);
        DAC->DHR12R1 = 2048;   /* ~1,65 V  */
        delay(0xFFFFF);
        DAC->DHR12R1 = 3072;   /* ~2,47 V  */
        delay(0xFFFFF);
    }
}
