# Modul 14 — HAL Running LED (Tugas)

## Tujuan

Menyalakan keempat LED LD3–LD6 secara bergantian (*running LED*) memakai HAL
dengan periode 250 ms.

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

Tidak ada rangkaian tambahan. Lihat `assets/wiring.svg`.

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Satu LED menyala bergantian dari PD12 sampai PD15 dengan periode 250 ms.

## Troubleshooting

- **Semua LED menyala:** pastikan seluruh pin di-reset sebelum menyalakan satu.
- **LED tidak menyala:** periksa clock GPIOD dan urutan pin.
