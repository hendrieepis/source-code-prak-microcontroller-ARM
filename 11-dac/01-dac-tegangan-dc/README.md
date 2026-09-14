# Modul 11 — DAC: Tegangan DC

## Tujuan

Menghasilkan tegangan analog tetap (DC) melalui DAC1 (PA4) dengan mengubah
nilai register `DHR12R1`.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| DAC1 channel 1 | PA4 |
| Ground osiloskop | GND |

## Wiring

Hubungkan probe positif osiloskop ke PA4 dan probe negatif ke GND. Lihat
`assets/wiring.svg`.

## Konfigurasi

- DAC1 aktif, buffer output aktif
- `DHR12R1 = nilai` → $V_"out" = "nilai" times 3,3\/4095$

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Osiloskop/voltmeter menunjukkan level 0,00 V; 0,82 V; 1,65 V; dan 2,47 V
bergantian tiap detik.

## Troubleshooting

- **Tegangan nol:** pastikan `DAC_CR_EN1` diset dan PA4 bermode analog.
- **Nilai tidak linier:** periksa `DHR12R1` pada rentang 0–4095.
