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
    USART2->CR1 = USART_CR1_TE | USART_CR1_UE;   /* hanya TX */
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

static void delay(uint32_t n)
{
    while (n--) {}
}

int main(void)
{
    usart2_init();

    for (;;)
    {
        uart_puts("Hello from STM32F4DISCOVERY\r\n");
        delay(0x5FFFFF);
    }
}
