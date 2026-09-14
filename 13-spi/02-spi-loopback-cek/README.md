# Modul 13 — SPI Loopback Verifikasi

## Tujuan

Mengirim pola byte melalui SPI1 master dan memverifikasi byte yang diterima
sama dengan yang dikirim (loopback).

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| SPI1 SCK | PA5 |
| SPI1 MISO | PA6 |
| SPI1 MOSI | PA7 |
| USART2 TX | PA2 |

## Wiring

Jumperkan PA7 (MOSI) ke PA6 (MISO); PA2 ke RX adapter USB-Serial. Lihat
`assets/wiring.svg`.

## Konfigurasi

- 16 byte uji: `kirim = i * 17`
- SPI1 master, mode 3, 8-bit

## Build dan upload

```bash
pio run
pio run -t upload
pio device monitor -b 9600
```

## Hasil yang diharapkan

Terminal menampilkan tiap pasangan `kirim`/`terima` dan berakhir dengan
`HASIL: PASS`.

## Troubleshooting

- **HASIL: FAIL:** periksa jumper loopback, CPOL/CPHA, dan prescaler.
- **Beberapa byte salah:** periksa panjang kabel SPI (jaga tetap pendek).
