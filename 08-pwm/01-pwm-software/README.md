# Modul 08 — PWM Software (0,5 s, duty 50%)

## Tujuan

Membuat PWM *software* dengan TIM2: LED dinyalakan pada 0,25 s dan dimatikan
pada 0,5 s menggunakan perbandingan nilai counter.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Konfigurasi timer

- Clock APB1 timer = 16 MHz
- `PSC = 8000 - 1` → tick 0,5 ms
- `ARR = 1000 - 1` → overflow 0,5 s
- LED nyala saat `CNT == 500`, mati saat `CNT == 999` → duty 50%

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| LED | PD12 |

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

LED menyala 0,25 s dan mati 0,25 s (periode 0,5 s, duty 50%).

## Troubleshooting

- **Duty tidak tepat:** periksa nilai pembanding counter dan `ARR`.
- **Upload gagal:** periksa kabel mini-USB dan driver ST-LINK.
