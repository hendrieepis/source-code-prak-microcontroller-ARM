# Modul 13 — SPI Master

## Tujuan

Mengonfigurasi SPI1 sebagai master dan mengirim byte berurutan sambil
menampilkan hasil terima melalui UART.

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

Jumperkan PA7 (MOSI) ke PA6 (MISO) untuk loopback. Hubungkan PA2 ke RX adapter
USB-Serial. Lihat `assets/wiring.svg`.

## Konfigurasi

- SPI1 master, 8-bit, mode 3 (CPOL=1, CPHA=1), MSB first
- Baudrate prescaler = fPCLK/4
- Software NSS (`SSM`/`SSI` = 1)

## Build dan upload

```bash
pio run
pio run -t upload
pio device monitor -b 9600
```

## Hasil yang diharapkan

Terminal menampilkan `kirim/terima = 0xNN` dengan nilai byte yang bertambah.

## Troubleshooting

- **Nilai terima 0x00/0xFF:** periksa jumper loopback PA7–PA6 dan mode clock.
- **Tidak ada data:** pastikan `SPI_CR1_SPE` diset dan pin AF5 benar.
