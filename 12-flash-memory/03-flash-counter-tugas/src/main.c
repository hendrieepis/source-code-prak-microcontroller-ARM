#include "stm32f4xx.h"

#define FLASH_KEY1   0x45670123U
#define FLASH_KEY2   0xCDEF89ABU
#define PARAM_ADDR   0x0800C000U   /* awal Sector 3 */
#define SECTOR       3U

static void flash_unlock(void)
{
    if (FLASH->CR & FLASH_CR_LOCK)
    {
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
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
    volatile uint32_t counter;

    /* Baca nilai lama, lalu hapus sektor dan tulis nilai baru. */
    counter = *(__IO uint32_t *)PARAM_ADDR;
    if (counter == 0xFFFFFFFFU)
    {
        counter = 0;             /* flash masih kosong */
    }
    counter++;

    flash_unlock();
    flash_erase_sector(SECTOR);
    flash_program_word(PARAM_ADDR, counter);
    FLASH->CR |= FLASH_CR_LOCK;

    for (;;)
    {
    }
}
