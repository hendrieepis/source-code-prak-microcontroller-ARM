#include "stm32f4xx.h"

#define NSAMPLES 32

/* Gelombang gigi gergaji 12-bit (0--4095). */
static const uint16_t saw[NSAMPLES] = {
       0,  132,  264,  396,  528,  660,  793,  925,
    1057, 1189, 1321, 1453, 1585, 1717, 1849, 1981,
    2113, 2245, 2377, 2510, 2642, 2774, 2906, 3038,
    3170, 3302, 3434, 3566, 3698, 3830, 3962, 4095
};

static void dac_dma_wave_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_DACEN | RCC_APB1ENR_TIM6EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_DMA1EN;

    GPIOA->MODER |= (3U << (4 * 2));   /* PA4 analog (DAC_OUT1) */

    /* TIM6: event update menjadi trigger DAC. */
    TIM6->PSC = 0;
    TIM6->ARR = 100;                   /* f_update = 16 MHz / 101 */
    TIM6->CR2 |= TIM_CR2_MMS_1;        /* MMS = 010 (update)      */
    TIM6->CR1 |= TIM_CR1_CEN;

    /* DMA1 Stream5, channel 7 (DAC1), memory->peripheral, halfword, circular. */
    DMA1_Stream5->CR = 0;
    while (DMA1_Stream5->CR & DMA_SxCR_EN) { }
    DMA1_Stream5->PAR  = (uint32_t)&DAC->DHR12R1;
    DMA1_Stream5->M0AR = (uint32_t)saw;
    DMA1_Stream5->NDTR = NSAMPLES;
    DMA1_Stream5->CR = (7U << 25)          /* CHSEL = 7 (DAC1) */
                     | (1U << 6)           /* DIR   = M->P     */
                     | DMA_SxCR_CIRC
                     | DMA_SxCR_MINC
                     | DMA_SxCR_PSIZE_0    /* halfword */
                     | DMA_SxCR_MSIZE_0;   /* halfword */
    DMA1_Stream5->CR |= DMA_SxCR_EN;

    /* DAC1: trigger dari TIM6 TRGO, DMA aktif, buffer output aktif. */
    DAC->CR |= DAC_CR_TSEL1_1      /* TSEL1 = 010 (TIM6 TRGO) */
             | DAC_CR_TEN1
             | DAC_CR_DMAEN1
             | DAC_CR_EN1;
}

int main(void)
{
    dac_dma_wave_init();

    for (;;)
    {
    }
}
