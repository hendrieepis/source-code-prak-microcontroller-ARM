# Modul 06 — External Interrupt: Tombol B1 (PA0) Membalik LED

## Tujuan

Menggunakan interupsi eksternal (EXTI0) dari tombol B1 (PA0) untuk membalik
kondisi keempat LED, dengan pendekatan CMSIS + register (framework `stm32cube`).

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| LED LD4–LD6 | PD12–PD15 |
| Tombol B1 (EXTI0) | PA0 |

## Wiring

Semua on-board; diagram pada `assets/wiring.svg`.

## Build dan upload

```bash
pio run
pio run -t upload
```

## Program

`src/main.c` menghubungkan EXTI0 ke PA0 (`SYSCFG->EXTICR`), mengaktifkan pemicu
rising (`EXTI->RTSR`), dan mengaktifkan `EXTI0_IRQn` pada NVIC. Di dalam
`EXTI0_IRQHandler()` pending bit dibersihkan dan LED di-toggle.

## Hasil yang diharapkan

Setiap kali tombol B1 ditekan, keempat LED berganti kondisi (nyala↔mati).

## Troubleshooting

- **Interupsi tidak jalan:** pastikan clock SYSCFG aktif dan EXTI0 di-*unmask*.
- **Banyak interupsi sekali tekan:** bersihkan `EXTI->PR` di handler.
- **Upload gagal:** periksa kabel mini-USB dan driver ST-LINK.
