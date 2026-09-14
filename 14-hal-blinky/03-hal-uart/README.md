# Modul 14 — HAL UART

## Tujuan

Mengirim teks melalui USART2 memakai HAL (`HAL_UART_Init()` dan
`HAL_UART_Transmit()`).

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| USART2 TX | PA2 |
| USART2 RX | PA3 |

## Wiring

PA2 (TX) ke RX adapter USB-Serial, PA3 (RX) ke TX adapter, GND ke GND. Lihat
`assets/wiring.svg`.

## Konfigurasi

- USART2, 9600 baud, 8N1
- Pin AF7 dikonfigurasi di `HAL_UART_MspInit`

## Build dan upload

```bash
pio run
pio run -t upload
pio device monitor -b 9600
```

## Hasil yang diharapkan

Terminal menampilkan `Hello HAL UART` setiap detik.

## Troubleshooting

- **Tidak ada output:** periksa `HAL_UART_MspInit` dan kabel TX.
- **Karakter rusak:** samakan baudrate 9600.
