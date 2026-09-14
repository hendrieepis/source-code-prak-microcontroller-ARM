#include "stm32f4xx.h"

#define FLASH_KEY1   0x45670123U
#define FLASH_KEY2   0xCDEF89ABU
#define USER_ADDR    0x08008000U   /* awal Sector 2 */
#define SECTOR       2U
#define DATA         0xABCDEF01U

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
    uint32_t i;
    volatile uint32_t ok = 1;

    flash_unlock();
    flash_erase_sector(SECTOR);

    for (i = 0; i < 8; i++)
    {
        flash_program_word(USER_ADDR + (i * 4), DATA);
    }

    flash_lock();

    for (i = 0; i < 8; i++)
    {
        if (*(__IO uint32_t *)(USER_ADDR + (i * 4)) != DATA)
        {
            ok = 0;
        }
    }

    for (;;)
    {
    }
}
