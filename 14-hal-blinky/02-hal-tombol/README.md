# Modul 14 — HAL Tombol

## Tujuan

Membaca tombol USER (PA0) memakai HAL dan menyalakan LED dengan *debounce*
berbasis `HAL_GetTick()`.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| Tombol USER | PA0 |
| LED hijau (LD4) | PD12 |

## Wiring

Tombol USER sudah terpasang di board. Lihat `assets/wiring.svg`.

## Konfigurasi

- Tombol: input tanpa pull (PU/PD eksternal di board)
- Debounce 50 ms berbasis `HAL_GetTick()`

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Setiap penekanan tombol membalik kondisi LED PD12.

## Troubleshooting

- **LED tidak berubah:** periksa pin tombol (PA0) dan debounce.
- **Beberapa kali toggle per tekan:** perbesar nilai debounce.
