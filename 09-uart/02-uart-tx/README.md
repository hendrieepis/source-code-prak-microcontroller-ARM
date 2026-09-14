# Modul 09 — UART: Transmit (TX)

## Tujuan

Mengirim teks melalui USART2 secara periodik (mode transmit).

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| USART2 TX | PA2 |

## Wiring

PA2 (TX) ke RX adapter USB-Serial, GND ke GND. Lihat `assets/wiring.svg`.

## Build dan upload

```bash
pio run
pio run -t upload
pio device monitor -b 9600
```

## Hasil yang diharapkan

Terminal menampilkan `Hello from STM32F4DISCOVERY` berulang.

## Troubleshooting

- **Tidak tampil:** periksa kabel TX dan baudrate.
- **Karakter asing:** samakan baudrate (9600).
