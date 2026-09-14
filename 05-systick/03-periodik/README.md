# Modul 05 — SysTick: Pola Periodik

## Tujuan

Membuat pola LED periodik (nyala 500 ms, mati 500 ms) dengan interrupt SysTick.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube` (CMSIS)

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| LED LD4–LD6 | PD12–PD15 |

## Wiring

LED sudah terpasang di board.

![Wiring keempat LED PD12–PD15](assets/wiring.svg)

## Build dan upload

```bash
pio run
pio run -t upload
```

## Program

`src/main.c` memakai SysTick 1 ms dan penghitung di dalam `SysTick_Handler()`
untuk membentuk pola 50% duty dengan periode 1 detik.

## Hasil yang diharapkan

LED menyala 500 ms lalu mati 500 ms secara berulang.

## Troubleshooting

- **Pola tidak konsisten:** pastikan perhitungan periode pada handler benar
  (1000 hitungan = 1 detik pada tick 1 ms).
- **Upload gagal:** periksa kabel mini-USB dan driver ST-LINK.
