# Modul 12 — Flash Memory: Parameter

## Tujuan

Menyimpan parameter (magic dan nilai) di flash, lalu membacanya kembali dan
menampilkan hasil melalui UART.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| USART2 TX | PA2 |

## Wiring

PA2 (TX) ke RX adapter USB-Serial, GND ke GND.

## Konfigurasi

- Sektor uji: **Sector 3** (`0x0800C000`)
- Parameter: `magic = 0x55AA1234`, `nilai = 12345`
- UART 9600 baud

## Build dan upload

```bash
pio run
pio run -t upload
pio device monitor -b 9600
```

## Hasil yang diharapkan

Terminal menampilkan:

```text
magic = 0x55AA1234
nilai = 0x00003039
```

## Troubleshooting

- **Nilai 0xFFFFFFFF:** sektor belum terprogram; periksa langkah erase/program.
- **Tidak ada output:** periksa kabel UART dan baudrate.
- **Gagal program:** flash harus di-*unlock* lebih dahulu.
