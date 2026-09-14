#include "stm32f4xx.h"
void Delay(__IO uint32_t delayparm);

/* Clock default setelah reset = HSI 16 MHz (tanpa konfigurasi PLL). */
#define CPU_HZ        16000000UL
/* Isi loop Delay = 5 instruksi (ldr,subs,str,cmp,bne) ~ 7 cycle di Cortex-M4. */
#define LOOP_CYCLES   7U
/* Hitungan untuk tunda 1 detik:  CPU_HZ / LOOP_CYCLES  =  16000000 / 7 */
#define DELAY_1S      (CPU_HZ / LOOP_CYCLES)

int main(void)
{
    /* Aktifkan clock GPIOD melalui pointer RCC (struct). */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    /* Konfigurasi PD13 sebagai output (memakai pointer GPIOD). */
    GPIOD->MODER &= ~(3U << (13 * 2));
    GPIOD->MODER |=  (1U << (13 * 2));

    while (1)
    {
        GPIOD->BSRR = (1U << 13);          /* set   PD13 (LED menyala) */
        Delay(DELAY_1S);
        GPIOD->BSRR = (1U << (13 + 16));   /* reset PD13 (LED mati)    */
        Delay(DELAY_1S);
    }
}

void Delay(__IO uint32_t delayparm)
{
    while (delayparm--);
}