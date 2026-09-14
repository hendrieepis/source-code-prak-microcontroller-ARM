#include "stm32f4xx.h"
#include <math.h>

#define NSAMPLES 512

static uint16_t sine[NSAMPLES];

static void dac_dma_wave_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_DACEN | RCC_APB1ENR_TIM6EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_DMA1EN;

    GPIOA->MODER |= (3U << (4 * 2));   /* PA4 analog */

    TIM6->PSC = 0;
    TIM6->ARR = 62;                    /* f_update = 16 MHz / 63 */
    TIM6->CR2 |= TIM_CR2_MMS_1;
    TIM6->CR1 |= TIM_CR1_CEN;

    DMA1_Stream5->CR = 0;
    while (DMA1_Stream5->CR & DMA_SxCR_EN) { }
    DMA1_Stream5->PAR  = (uint32_t)&DAC->DHR12R1;
    DMA1_Stream5->M0AR = (uint32_t)sine;
    DMA1_Stream5->NDTR = NSAMPLES;
    DMA1_Stream5->CR = (7U << 25) | (1U << 6) | DMA_SxCR_CIRC
                     | DMA_SxCR_MINC | DMA_SxCR_PSIZE_0 | DMA_SxCR_MSIZE_0;
    DMA1_Stream5->CR |= DMA_SxCR_EN;

    DAC->CR |= DAC_CR_TSEL1_1 | DAC_CR_TEN1 | DAC_CR_DMAEN1 | DAC_CR_EN1;
}

int main(void)
{
    for (int i = 0; i < NSAMPLES; i++)
    {
        /* 512 titik, amplitudo 0..255 */
        sine[i] = (uint16_t)(128 + (int16_t)(127 * sinf(2.0f * 3.14159265f * i / NSAMPLES)));
    }

    dac_dma_wave_init();

    for (;;)
    {
    }
}
