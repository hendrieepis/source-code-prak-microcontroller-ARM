# Modul 02 — Tugas 4: Running LED

## Tujuan

Menyalakan LED PD12--PD15 secara bergiliran (running LED) memakai register
`BSRR`.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| LED | Pin |
|---|---|
| LD4 (hijau) | PD12 |
| LD3 (oranye) | PD13 |
| LD5 (merah) | PD14 |
| LD6 (biru) | PD15 |

## Wiring

Tidak ada rangkaian tambahan.

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Satu LED menyala bergiliran dari PD12 sampai PD15 dengan jeda ±0,25 detik.

## Troubleshooting

- **Semua LED menyala:** pastikan LED sebelumnya di-reset sebelum menyalakan
  LED berikutnya.
