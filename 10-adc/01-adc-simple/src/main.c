#include "stm32f4xx.h"

static void adc_init(void)
{
    /* Clock ADC1 (APB2) dan GPIOC. */
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    /* PC0 sebagai input analog (MODER = 11). */
    GPIOC->MODER |= (3U << (0 * 2));

    /* Prescaler ADC = PCLK2/4 (ADCPRE = 01). */
    ADC->CCR = ADC_CCR_ADCPRE_0;

    ADC1->CR1 = 0;              /* resolusi 12-bit (RES = 00) */
    ADC1->CR2 = 0;
    ADC1->SQR1 = 0;             /* hanya 1 konversi */
    ADC1->SQR3 = 10;            /* konversi pertama = channel 10 (PC0) */
    ADC1->SMPR1 |= (7U << 0);   /* sample time channel 10 = 480 siklus */

    ADC1->CR2 |= ADC_CR2_ADON;  /* nyalakan ADC */
}

static uint16_t adc_read(void)
{
    ADC1->CR2 |= ADC_CR2_SWSTART;              /* mulai konversi */
    while (!(ADC1->SR & ADC_SR_EOC)) { }       /* tunggu selesai */
    return (uint16_t)ADC1->DR;                 /* baca hasil     */
}

int main(void)
{
    adc_init();

    volatile uint16_t nilai = 0;   /* amati lewat debugger */

    for (;;)
    {
        nilai = adc_read();
    }
}
