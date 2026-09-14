#include "stm32f4xx.h"
void Delay(__IO uint32_t delayparm);

#define CPU_HZ        16000000UL
#define LOOP_CYCLES   7U
#define DELAY_1S      (CPU_HZ / LOOP_CYCLES)

int main(void)
{
    *((uint32_t volatile *)(0x40023810))=0x08; // RCC->AHB1RSTR --> reset PORTD
    *((uint32_t volatile *)(0x40023810))=0x00; // RCC->AHB1RSTR
    *((uint32_t volatile *)(0x40023830))=0x08; // RCC->AHB1ENR  --> clock GPIOD
    *((uint32_t volatile *)(0x40020C00))=0x55000000; // PD12, PD13, PD14, PD15 output

    while(1)
    {
        for (uint32_t i = 12; i <= 15; i++)
        {
            *((uint32_t volatile *)(0x40020C18))=(1U << i);        // GPIOD->BSRR --> SET PD(i)
            Delay(DELAY_1S / 4);                                   // ~0,25 detik
            *((uint32_t volatile *)(0x40020C18))=(1U << (i + 16)); // GPIOD->BSRR --> RESET PD(i)
        }
    }
}

void Delay(__IO uint32_t delayparm) {
    while (delayparm--);
}
