# Modul 11 — DAC: Gelombang dengan DMA

## Tujuan

Membangkitkan gelombang analog (gigi gergaji) dari tabel sampel memakai DAC1,
DMA1, dan trigger TIM6.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| DAC1 channel 1 | PA4 |
| Ground osiloskop | GND |

## Wiring

Probe positif osiloskop ke PA4, negatif ke GND. Lihat `assets/wiring.svg`.

## Konfigurasi

- TIM6 update event → trigger DAC (MMS = 010)
- DMA1 Stream5 channel 7, memory→peripheral, 16-bit, circular
- 32 sampel, `ARR = 100` → $f_"update" = 16\ "MHz"\/101$

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Osiloskop menampilkan gelombang gigi gergaji berulang pada PA4.

## Troubleshooting

- **Tidak ada gelombang:** pastikan DMA `CIRC` dan `MINC` diset serta
  `DAC_CR_DMAEN1` dan `DAC_CR_TEN1` aktif.
- **Frekuensi salah:** periksa `ARR`/`PSC` TIM6 dan jumlah sampel.
