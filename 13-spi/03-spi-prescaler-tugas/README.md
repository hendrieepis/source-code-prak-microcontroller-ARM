# Modul 13 — SPI Prescaler (Tugas)

## Tujuan

Mengubah prescaler SPI1 menjadi fPCLK/16 dan fPCLK/64, lalu mengamati
pengaruhnya.

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

Jumperkan PA7 (MOSI) ke PA6 (MISO); PA2 ke RX adapter USB-Serial.

## Konfigurasi

- `spi1_set_prescaler(3)` → fPCLK/16
- `spi1_set_prescaler(5)` → fPCLK/64

## Build dan upload

```bash
pio run
pio run -t upload
pio device monitor -b 9600
```

## Hasil yang diharapkan

Terminal menampilkan dua kali `terima = 0xA5` (loopback) dengan keterangan
prescaler yang berbeda.

## Troubleshooting

- **Terima bukan 0xA5:** periksa jumper loopback dan mode SPI.
- **Pengiriman lambat:** itulah efek prescaler besar (clock lebih rendah).
