# Modul 03 — Akses I/O melalui Pointer: Input Tombol (PA0) → LED (PD15)

## Tujuan

Membaca tombol **B1** (PA0) dan mengendalikan **LED LD6** (PD15) dengan
mengakses register melalui **pointer/struct** `GPIOA` dan `GPIOD`.

## Board target

- Board: **ST STM32F4DISCOVERY**
- ID board PlatformIO: `disco_f407vg`
- Framework: `stm32cube` (header CMSIS `stm32f4xx.h`)

## Kebutuhan perangkat keras

- Board STM32F4Discovery
- Kabel **mini-USB**

## Pin yang dipakai

| Fungsi          | Pin  | Sifat        |
|-----------------|------|--------------|
| LED LD6 (biru)  | PD15 | active-high  |
| Tombol B1       | PA0  | active-high  |

## Wiring

LED dan tombol sudah terpasang di board.

![Wiring tombol B1 (PA0) dan LED LD6 (PD15)](assets/wiring.svg)

## Build dan upload

```bash
pio run
pio run -t upload
```

## Program

`src/main.c` — membaca `GPIOA->IDR` bit 0; bila HIGH, `GPIOD->BSRR` men-set
PD15 (LED menyala), bila LOW men-reset PD15.

## Hasil yang diharapkan

LED LD6 menyala selama tombol B1 ditekan dan mati saat dilepas.

## Troubleshooting

- **LED tidak merespons:** pastikan `clock` GPIOA aktif (untuk membaca
  `GPIOA->IDR`) dan PD15 sudah output.
- **Polaritas terbalik:** tombol board ini active-high (ditekan = HIGH).
- **Upload gagal:** periksa kabel mini-USB dan driver ST-LINK.
