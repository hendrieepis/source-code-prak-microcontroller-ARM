#include "stm32f4xx.h"

#define APB1_CLK  16000000U
#define BAUDRATE  9600U

static void usart2_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~((3U << (2 * 2)) | (3U << (3 * 2)));
    GPIOA->MODER |=  ((2U << (2 * 2)) | (2U << (3 * 2)));
    GPIOA->AFR[0] &= ~((0xFU << (2 * 4)) | (0xFU << (3 * 4)));
    GPIOA->AFR[0] |=  ((7U << (2 * 4)) | (7U << (3 * 4)));

    USART2->BRR = (APB1_CLK + BAUDRATE / 2) / BAUDRATE;
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

    /* Aktifkan interrupt RXNE dan NVIC. */
    USART2->CR1 |= USART_CR1_RXNEIE;
    NVIC_EnableIRQ(USART2_IRQn);
}

static void uart_putchar(unsigned char c)
{
    while (!(USART2->SR & USART_SR_TXE)) { }
    USART2->DR = c;
}

static void uart_puts(const char *s)
{
    while (*s)
    {
        uart_putchar((unsigned char)*s++);
    }
}

int main(void)
{
    usart2_init();
    uart_puts("Init complete! Hello World!\r\n");

    while (1)
    {
    }
}

/* Interrupt Rx: gema karakter yang diterima. */
void USART2_IRQHandler(void)
{
    if (USART2->SR & USART_SR_RXNE)
    {
        char c = (char)USART2->DR;   /* membaca DR membersihkan RXNE */
        USART2->DR = c;              /* kirim balik                   */
    }
}
