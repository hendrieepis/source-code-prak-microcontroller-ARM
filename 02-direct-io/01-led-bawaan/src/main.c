#include "stm32f4xx.h"
void Delay(__IO uint32_t delayparm);

/* Clock default setelah reset = HSI 16 MHz (tanpa konfigurasi PLL). */
#define CPU_HZ        16000000UL
/* Isi loop Delay = 5 instruksi (ldr,subs,str,cmp,bne) ~ 7 cycle di Cortex-M4. */
#define LOOP_CYCLES   7U
/* Hitungan untuk tunda 1 detik:  CPU_HZ / LOOP_CYCLES  =  16000000 / 7 */
#define DELAY_1S      (CPU_HZ / LOOP_CYCLES)

int main() {
//reset
    *((uint32_t volatile *)(0x40023810))=0x08; // RCC->AHB1RSTR --> reset PORTD
    *((uint32_t volatile *)(0x40023810))=0x00; // RCC->AHB1RSTR
    *((uint32_t volatile *)(0x40023830))=0x08; // RCC->AHB1ENR  --> IO PORTD Clock Enable
    *((uint32_t volatile *)(0x40020C00))=0x01000000;//GPIOD->MODER-> PORTD.12 Output
    while(1)
    {
       *((uint32_t volatile *)(0x40020C18))=0x1000;     //GPIOD->BSRR -->SET PORTD.12
       Delay(DELAY_1S);                                  // tunda ~1 detik
       *((uint32_t volatile *)(0x40020C18))=0x10000000; //GPIOD->BSRR -->RESET PORTD.12
       Delay(DELAY_1S);                                  // tunda ~1 detik
    }
}

void Delay(__IO uint32_t delayparm) {
    while (delayparm--);
}
