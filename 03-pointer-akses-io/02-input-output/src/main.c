#include "stm32f4xx.h"

int main(void)
{
    /* Aktifkan clock GPIOD dan GPIOA melalui pointer RCC. */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOAEN;

    /* PD15 sebagai output; PA0 tetap masukan (nilai reset MODER = 0). */
    GPIOD->MODER &= ~(3U << (15 * 2));
    GPIOD->MODER |=  (1U << (15 * 2));

    while (1)
    {
        if (GPIOA->IDR & (1U << 0))        /* PA0 HIGH (tombol ditekan) */
        {
            GPIOD->BSRR = (1U << 15);      /* set   PD15 (LED menyala)  */
        }
        else
        {
            GPIOD->BSRR = (1U << (15 + 16)); /* reset PD15 (LED mati)   */
        }
    }
}
