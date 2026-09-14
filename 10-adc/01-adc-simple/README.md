# Modul 10 — ADC1 Sederhana (Polling)

## Tujuan

Membaca tegangan analog melalui ADC1 (channel 10, PC0) dengan metode polling.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| ADC1 channel 10 | PC0 |
| Potensiometer ujung 1 | GND |
| Potensiometer ujung 3 | +3V3 |

## Wiring

Hubungkan potensiometer: ujung 1 ke GND, ujung 3 ke +3V3, kaki tengah (wiper)
ke PC0. Lihat `assets/wiring.svg`.

## Konfigurasi

- Prescaler ADC = PCLK2/4
- Resolusi 12-bit (0–4095)
- Satu konversi, channel 10, sample time 480 siklus

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Nilai `nilai` (0–4095) berubah saat potensiometer diputar; amati melalui
debugger (watch variable).

## Troubleshooting

- **Nilai tetap:** pastikan wiper terhubung ke PC0 dan pin lain ke +3V3/GND.
- **Nilai acak:** periksa prescaler dan sample time.
