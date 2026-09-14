#include "stm32f4xx.h"

#define APB1_CLK     16000000U
#define BAUDRATE     9600U

#define FLASH_KEY1   0x45670123U
#define FLASH_KEY2   0xCDEF89ABU
#define PARAM_ADDR   0x0800C000U   /* awal Sector 3 */
#define SECTOR       3U
#define MAGIC        0x55AA1234U

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

static void uart_puthex(uint32_t v)
{
    static const char hex[] = "0123456789ABCDEF";
    int i;

    for (i = 28; i >= 0; i -= 4)
    {
        uart_putchar((unsigned char)hex[(v >> i) & 0xF]);
    }
}

static void flash_unlock(void)
{
    if (FLASH->CR & FLASH_CR_LOCK)
    {
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

static void flash_lock(void)
{
    FLASH->CR |= FLASH_CR_LOCK;
}

static void flash_wait(void)
{
    while (FLASH->SR & FLASH_SR_BSY) { }
}

static void flash_erase_sector(uint32_t sector)
{
    flash_wait();
    FLASH->CR |= FLASH_CR_SER | FLASH_CR_PSIZE_1;
    FLASH->CR = (FLASH->CR & ~FLASH_CR_SNB) | (sector << FLASH_CR_SNB_Pos);
    FLASH->CR |= FLASH_CR_STRT;
    flash_wait();
    FLASH->CR &= ~FLASH_CR_SER;
}

static void flash_program_word(uint32_t addr, uint32_t data)
{
    flash_wait();
    FLASH->CR |= FLASH_CR_PG | FLASH_CR_PSIZE_1;
    *(__IO uint32_t *)addr = data;
    flash_wait();
    FLASH->CR &= ~FLASH_CR_PG;
}

int main(void)
{
    uint32_t magic;
    uint32_t nilai;

    uart2_init();

    /* Tulis parameter ke flash. */
    flash_unlock();
    flash_erase_sector(SECTOR);
    flash_program_word(PARAM_ADDR + 0, MAGIC);
    flash_program_word(PARAM_ADDR + 4, 12345U);
    flash_lock();

    /* Baca kembali parameter dari flash. */
    magic = *(__IO uint32_t *)(PARAM_ADDR + 0);
    nilai = *(__IO uint32_t *)(PARAM_ADDR + 4);

    uart_putstr("magic = 0x");
    uart_puthex(magic);
    uart_putstr("\r\nnilai = ");
    uart_puthex(nilai);
    uart_putstr("\r\n");

    for (;;)
    {
    }
}
