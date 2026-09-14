# Modul 08 — Tugas: PWM Servo (20 ms, pulse 1,5 ms)

## Tujuan

Membangkitkan sinyal kontrol servo: periode 20 ms dengan lebar pulsa 1,5 ms
(posisi tengah) memakai TIM4 CH1 (PD12).

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Konfigurasi timer

- Clock APB1 timer = 16 MHz
- `PSC = 160 - 1` → tick 10 µs
- `ARR = 2000 - 1` → period 20 ms (50 Hz)
- `CCR1 = 150` → pulse 1,5 ms

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| Sinyal PWM servo | PD12 |

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Sinyal PWM 50 Hz dengan lebar pulsa 1,5 ms pada PD12.

## Troubleshooting

- **Pulsa tidak sesuai:** periksa `PSC`/`ARR`/`CCR1` terhadap clock timer.
- **Upload gagal:** periksa kabel mini-USB dan driver ST-LINK.
