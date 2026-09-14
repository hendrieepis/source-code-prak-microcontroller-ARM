# Modul 09 — UART: Echo (Polling)

## Tujuan

Membuat UART dua arah sederhana: setiap karakter yang diterima dikirim kembali
(echo), dengan USART2 dan polled I/O.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| USART2 TX | PA2 |
| USART2 RX | PA3 |
| Ground | GND |

## Wiring

Hubungkan PA2 ke RX adapter USB-Serial, PA3 ke TX adapter, dan GND ke GND
(TX/RX disilang). Lihat `assets/wiring.svg`.

## Konfigurasi

- Clock APB1 = 16 MHz; `BRR = 16e6 / 9600 ≈ 1667`
- AF7 untuk PA2/PA3

## Build dan upload

```bash
pio run
pio run -t upload
pio device monitor -b 9600
```

## Hasil yang diharapkan

Karakter yang dikirim dari terminal akan diterima kembali (echo).

## Troubleshooting

- **Tidak ada data:** pastikan TX/RX disilang dan baudrate sama (9600).
- **Karakter rusak:** periksa `BRR` terhadap clock APB1.
