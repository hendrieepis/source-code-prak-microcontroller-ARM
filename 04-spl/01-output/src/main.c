#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

/* Penunda busy-wait sederhana. */
void Delay(__IO uint32_t nCount)
{
    while (nCount--) {}
}

int main(void)
{
    /* Aktifkan clock GPIOD melalui SPL. */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* Konfigurasi PD12 sebagai output melalui SPL. */
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    while (1)
    {
        GPIO_SetBits(GPIOD, GPIO_Pin_12);   /* LED LD4 menyala */
        Delay(0xFFFFFF);
        GPIO_ResetBits(GPIOD, GPIO_Pin_12); /* LED LD4 mati    */
        Delay(0xFFFFFF);
    }
}
