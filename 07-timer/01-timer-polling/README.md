# Modul 07 — Timer: Timer Polling (1 kHz)

## Tujuan

Membangkitkan sinyal 1 kHz duty 50% pada pin PD12 memakai TIM2 dan pengecekan
flag overflow (polling).

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Konfigurasi timer

- Clock APB1 timer = 16 MHz (HSI)
- `PSC = 80 - 1` → tick 5 µs
- `ARR = 100 - 1` → overflow 500 µs
- Toggle PD12 setiap overflow → 1 kHz, duty 50%

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| Keluaran sinyal | PD12 |

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Sinyal kotak 1 kHz duty 50% pada PD12 (ukur dengan osiloskop/logic analyzer).

## Troubleshooting

- **Frekuensi tidak sesuai:** sesuaikan `PSC`/`ARR` terhadap clock APB1 timer
  yang sebenarnya.
- **Upload gagal:** periksa kabel mini-USB dan driver ST-LINK.
