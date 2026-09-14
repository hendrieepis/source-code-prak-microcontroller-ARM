# Modul 11 — DAC: Sinus (Tugas)

## Tujuan

Membangkitkan sinyal sinus dengan 512 titik sampel dan amplitudo maksimum 255.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`
- Flag tambahan: `-lm` (fungsi `sinf`)

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| DAC1 channel 1 | PA4 |
| Ground osiloskop | GND |

## Wiring

Probe positif osiloskop ke PA4, negatif ke GND. Lihat `assets/wiring.svg`.

## Konfigurasi

- Tabel 512 sampel: `128 + 127*sin(2*pi*i/512)`
- TIM6 trigger + DMA1 Stream5 channel 7, circular

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Osiloskop menampilkan gelombang sinus berulang pada PA4.

## Troubleshooting

- **Tidak ada keluaran:** pastikan `-lm` ikut ter-link dan DMA aktif.
- **Bentuk tidak halus:** periksa jumlah sampel dan `ARR` TIM6.
