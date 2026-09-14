# Modul 05 — SysTick: Blinky LED via Interrupt

## Tujuan

Membuat LED PD12–PD15 berkedip menggunakan interrupt SysTick (berbasis CMSIS),
tanpa SPL.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube` (CMSIS)

## Kebutuhan perangkat keras

- Board STM32F4Discovery
- Kabel **mini-USB**

## Pin yang dipakai

| Fungsi | Pin | Sifat |
|---|---|---|
| LED LD4 | PD12 | active-high |
| LED LD3 | PD13 | active-high |
| LED LD5 | PD14 | active-high |
| LED LD6 | PD15 | active-high |

## Wiring

LED sudah terpasang di board.

![Wiring keempat LED PD12–PD15](assets/wiring.svg)

## Build dan upload

```bash
pio run
pio run -t upload
```

## Program

`src/main.c` mengonfigurasi `SysTick_Config(SystemCoreClock / 1000)` (interupsi
1 ms) dan membalik kondisi LED di dalam `SysTick_Handler()`.

## Hasil yang diharapkan

LED berkedip dengan frekuensi pembalikan 500 Hz (dapat diamati dengan
osilokop).

## Troubleshooting

- **LED tidak berubah:** pastikan `SysTick_Handler()` terdefinisi dan
  `SysTick_Config()` dipanggil.
- **Upload gagal:** periksa kabel mini-USB dan driver ST-LINK.
