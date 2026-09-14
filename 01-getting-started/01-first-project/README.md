# Modul 01 — Getting Started (Proyek Pertama)

## Tujuan

Membuat proyek PlatformIO pertama untuk STM32F4Discovery dan menyalakan LED LD3
(PD13) secara berkedip sebagai program Direct IO pertama.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`
- Kabel: **mini-USB**

## Pin yang dipakai

| Perangkat | Pin |
|---|---|
| LED LD3 (oranye) | PD13 |
| GND (jika perlu) | GND |

## Wiring

Tidak ada rangkaian tambahan; LED LD3 sudah terpasang di board. Lihat
`assets/wiring.svg`.

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

LED LD3 (oranye) berkedip: menyala ±1 detik, mati ±1 detik, berulang.

## Troubleshooting

- **LED diam:** pastikan proyek memakai *board* `disco_f407vg` dan framework
  `stm32cube`, serta perintah *Upload* (bukan hanya *Build*) dijalankan.
- **Upload gagal:** gunakan kabel **mini-USB** pada port ST-Link dan tutup
  aplikasi lain yang memakai port serial.
