# Modul 10 — ADC1 dengan DMA + UART

## Tujuan

Membaca tegangan analog melalui ADC1 memakai DMA (tanpa beban CPU) dan
menampilkan hasilnya melalui UART.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| ADC1 channel 10 | PC0 |
| USART2 TX | PA2 |
| USART2 RX | PA3 |

## Wiring

Potensiometer (ujung ke +3V3/GND, wiper ke PC0) dan UART ke adapter
USB-Serial. Lihat `assets/wiring.svg`.

## Konfigurasi

- ADC1 continuous + DMA2 Stream0 channel 0, 16-bit, circular
- UART 9600 baud

## Build dan upload

```bash
pio run
pio run -t upload
pio device monitor -b 9600
```

## Hasil yang diharapkan

Terminal menampilkan `read = <nilai>` (0–4095) secara berkala; nilai berubah
saat potensiometer diputar.

## Troubleshooting

- **Nilai diam:** pastikan DMA2 dan ADC clock aktif serta `ADC_CR2_DMA` diset.
- **Tidak ada output:** periksa kabel UART dan baudrate.
