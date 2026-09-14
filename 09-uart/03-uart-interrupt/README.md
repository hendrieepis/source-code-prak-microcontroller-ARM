# Modul 09 — UART: TX/RX dengan Interrupt

## Tujuan

Menggunakan interrupt RX (RXNE) USART2 untuk menggema karakter, sambil mengirim
pesan selamat datang saat start.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| USART2 TX | PA2 |
| USART2 RX | PA3 |

## Wiring

TX/RX disilang ke adapter USB-Serial, GND ke GND. Lihat `assets/wiring.svg`.

## Build dan upload

```bash
pio run
pio run -t upload
pio device monitor -b 9600
```

## Hasil yang diharapkan

Muncul pesan `Init complete! Hello World!`; setiap karakter yang dikirim
tergema kembali.

## Troubleshooting

- **Tidak ada gema:** pastikan `USART2_IRQn` diaktifkan dan `RXNEIE` diset.
- **Pesan rusak:** samakan baudrate.
