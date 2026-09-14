#include "stm32f4xx.h"

#define APB1_CLK  16000000U
#define BAUDRATE  9600U

static volatile uint16_t g_adc;   /* tujuan DMA */

static void uart2_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~((3U << (2 * 2)) | (3U << (3 * 2)));
    GPIOA->MODER |=  ((2U << (2 * 2)) | (2U << (3 * 2)));
    GPIOA->AFR[0] &= ~((0xFU << (2 * 4)) | (0xFU << (3 * 4)));
    GPIOA->AFR[0] |=  ((7U << (2 * 4)) | (7U << (3 * 4)));

    USART2->BRR = (APB1_CLK + BAUDRATE / 2) / BAUDRATE;
    USART2->CR1 = USART_CR1_TE | USART_CR1_UE;
}

static void uart_putchar(unsigned char c)
{
    while (!(USART2->SR & USART_SR_TXE)) { }
    USART2->DR = c;
}

static void uart_putstr(const char *s)
{
    while (*s)
    {
        uart_putchar((unsigned char)*s++);
    }
}

static void uart_putint(uint16_t v)
{
    char buf[6];
    int i = 0;

    if (v == 0)
    {
        uart_putchar('0');
        return;
    }
    while (v > 0 && i < 5)
    {
        buf[i++] = (char)('0' + (v % 10));
        v /= 10;
    }
    while (i--)
    {
        uart_putchar((unsigned char)buf[i]);
    }
}

static void delay(uint32_t n)
{
    while (n--) {}
}

static void adc_dma_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_DMA2EN;

    GPIOC->MODER |= (3U << (0 * 2));   /* PC0 analog */

    ADC->CCR = ADC_CCR_ADCPRE_0;       /* prescaler PCLK2/4 */

    ADC1->CR1 = 0;                     /* resolusi 12-bit */
    ADC1->CR2 = 0;
    ADC1->SQR1 = 0;
    ADC1->SQR3 = 10;                   /* channel 10 (PC0) */
    ADC1->SMPR1 |= (7U << 0);

    /* DMA2 Stream0, channel 0 (ADC1), peripheral->memory, halfword, circular. */
    DMA2_Stream0->CR = 0;
    while (DMA2_Stream0->CR & DMA_SxCR_EN) { }
    DMA2_Stream0->PAR  = (uint32_t)&ADC1->DR;
    DMA2_Stream0->M0AR = (uint32_t)&g_adc;
    DMA2_Stream0->NDTR = 1;
    DMA2_Stream0->CR = (0U << 25)          /* CHSEL = 0 (ADC1) */
                     | (0U << 6)           /* DIR  = P->M      */
                     | DMA_SxCR_CIRC
                     | DMA_SxCR_PSIZE_0    /* halfword */
                     | DMA_SxCR_MSIZE_0;   /* halfword */
    DMA2_Stream0->CR |= DMA_SxCR_EN;

    ADC1->CR2 |= ADC_CR2_DMA | ADC_CR2_DDS | ADC_CR2_CONT;
    ADC1->CR2 |= ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

int main(void)
{
    uart2_init();
    adc_dma_init();
    uart_putstr("ADC DMA siap\r\n");

    for (;;)
    {
        uart_putstr("read = ");
        uart_putint(g_adc);
        uart_putstr("\r\n");
        delay(0xFFFFF);
    }
}
