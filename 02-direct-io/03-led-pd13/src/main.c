#include "stm32f4xx.h"
void Delay(__IO uint32_t delayparm);

#define CPU_HZ        16000000UL
#define LOOP_CYCLES   7U
#define DELAY_1S      (CPU_HZ / LOOP_CYCLES)

int main() {
//reset
    *((uint32_t volatile *)(0x40023810))=0x08; // RCC->AHB1RSTR --> reset PORTD
    *((uint32_t volatile *)(0x40023810))=0x00; // RCC->AHB1RSTR
    *((uint32_t volatile *)(0x40023830))=0x08; // RCC->AHB1ENR  --> clock GPIOD
    *((uint32_t volatile *)(0x40020C00))=0x04000000; // GPIOD->MODER --> PD13 output
    while(1)
    {
       *((uint32_t volatile *)(0x40020C18))=0x2000;     // GPIOD->BSRR --> SET PD13
       Delay(DELAY_1S);
       *((uint32_t volatile *)(0x40020C18))=0x20000000; // GPIOD->BSRR --> RESET PD13 (bit 13+16)
       Delay(DELAY_1S);
    }
}

void Delay(__IO uint32_t delayparm) {
    while (delayparm--);
}
