# Modul 12 — Flash Memory: Counter (Tugas)

## Tujuan

Menyimpan nilai *counter* di flash; nilai bertambah setiap board dinyalakan
ulang.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Kebutuhan perangkat keras

- Board STM32F4Discovery + kabel mini-USB.

## Konfigurasi

- Sektor uji: **Sector 3** (`0x0800C000`)
- Nilai awal bila flash kosong (`0xFFFFFFFF`): 0

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Nilai `counter` bertambah setiap kali board di-reset/nyalakan ulang; amati
melalui debugger.

## Troubleshooting

- **Nilai tetap 1:** sektor harus dihapus sebelum program ulang.
- **Gagal tulis:** pastikan flash di-*unlock*.
