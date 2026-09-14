#include "stm32f4xx.h"

#define APB1_CLK  16000000U
#define BAUDRATE  9600U

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

static void uart_puthex8(uint8_t v)
{
    static const char hex[] = "0123456789ABCDEF";
    uart_putchar((unsigned char)hex[(v >> 4) & 0xF]);
    uart_putchar((unsigned char)hex[v & 0xF]);
}

static void spi1_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~((3U << (5 * 2)) | (3U << (6 * 2)) | (3U << (7 * 2)));
    GPIOA->MODER |=  ((2U << (5 * 2)) | (2U << (6 * 2)) | (2U << (7 * 2)));
    GPIOA->AFR[0] &= ~((0xFU << (5 * 4)) | (0xFU << (6 * 4)) | (0xFU << (7 * 4)));
    GPIOA->AFR[0] |=  ((5U << (5 * 4)) | (5U << (6 * 4)) | (5U << (7 * 4)));

    SPI1->CR1 = SPI_CR1_CPHA | SPI_CR1_CPOL | SPI_CR1_MSTR
              | SPI_CR1_SSI | SPI_CR1_SSM
              | (1U << 3)
              | SPI_CR1_SPE;
}

static void spi1_set_prescaler(uint32_t br)
{
    /* br: nilai 3 bit untuk field BR (bit 5:3).
       Contoh: 1 -> fPCLK/4, 3 -> fPCLK/16, 5 -> fPCLK/64. */
    SPI1->CR1 = (SPI1->CR1 & ~(7U << 3)) | ((br & 7U) << 3);
}

static uint8_t spi1_transfer(uint8_t data)
{
    while (!(SPI1->SR & SPI_SR_TXE)) { }
    *(volatile uint8_t *)&SPI1->DR = data;
    while (!(SPI1->SR & SPI_SR_RXNE)) { }
    return *(volatile uint8_t *)&SPI1->DR;
}

static void delay(uint32_t n)
{
    while (n--) {}
}

int main(void)
{
    uint8_t resp;

    spi1_init();
    uart2_init();

    spi1_set_prescaler(3);   /* fPCLK/16 */
    uart_putstr("prescaler = fPCLK/16\r\n");
    resp = spi1_transfer(0xA5);

    uart_putstr("terima = 0x");
    uart_puthex8(resp);
    uart_putstr("\r\n");

    spi1_set_prescaler(5);   /* fPCLK/64 */
    uart_putstr("prescaler = fPCLK/64\r\n");
    resp = spi1_transfer(0xA5);

    uart_putstr("terima = 0x");
    uart_puthex8(resp);
    uart_putstr("\r\n");

    for (;;)
    {
        delay(0xFFFFF);
    }
}
