#include "stm32f4xx.h"

#define APB1_CLK  16000000U
#define BAUDRATE  9600U

static void usart2_init(void)
{
    /* Clock USART2 (APB1) dan GPIOA. */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* PA2 (TX) dan PA3 (RX) sebagai alternate function. */
    GPIOA->MODER &= ~((3U << (2 * 2)) | (3U << (3 * 2)));
    GPIOA->MODER |=  ((2U << (2 * 2)) | (2U << (3 * 2)));

    /* AF7 (USART2) untuk PA2 dan PA3. */
    GPIOA->AFR[0] &= ~((0xFU << (2 * 4)) | (0xFU << (3 * 4)));
    GPIOA->AFR[0] |=  ((7U << (2 * 4)) | (7U << (3 * 4)));

    /* Baudrate. */
    USART2->BRR = (APB1_CLK + BAUDRATE / 2) / BAUDRATE;

    /* Aktifkan TX, RX, dan USART2. */
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

static unsigned char uart_getchar(void)
{
    while (!(USART2->SR & USART_SR_RXNE)) { }
    return (unsigned char)USART2->DR;
}

static void uart_putchar(unsigned char c)
{
    while (!(USART2->SR & USART_SR_TXE)) { }
    USART2->DR = c;
}

int main(void)
{
    usart2_init();

    for (;;)
    {
        uart_putchar(uart_getchar());   /* gema (echo) tiap karakter */
    }
}
