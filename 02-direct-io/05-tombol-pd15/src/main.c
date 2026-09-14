#include "stm32f4xx.h"

int main(void)
{
    /* reset dan aktifkan clock GPIOD (bit 3) serta GPIOA (bit 0) */
    *((uint32_t volatile *)(0x40023810))=0x09; // RCC->AHB1RSTR --> reset GPIOD + GPIOA
    *((uint32_t volatile *)(0x40023810))=0x00; // RCC->AHB1RSTR
    *((uint32_t volatile *)(0x40023830))=0x09; // RCC->AHB1ENR  --> clock GPIOD + GPIOA

    /* PD15 sebagai output; PA0 tetap masukan (nilai reset MODER = 0) */
    *((uint32_t volatile *)(0x40020C00))=0x40000000; // GPIOD->MODER --> PD15 output

    while(1)
    {
        /* baca GPIOA->IDR bit 0 (PA0 / tombol B1) */
        if ( (*((uint32_t volatile *)(0x40020010)) & (1<<0)) )
        {
            *((uint32_t volatile *)(0x40020C18))=0x8000;     // tombol ditekan --> SET PD15
        }
        else
        {
            *((uint32_t volatile *)(0x40020C18))=0x80000000; // tombol dilepas --> RESET PD15
        }
    }
}
