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

## Simulasi dengan Renode (tanpa hardware)

Jika board sedang tidak tersedia, firmware dapat diuji pada simulator
**Renode**. Firmware harus sudah dibangun lebih dahulu (`pio run`). Semua
perintah dijalankan dari root project (folder yang berisi `platformio.ini`).

Uji cepat (menjalankan emulasi, mencetak perubahan LED/tombol, lalu keluar):

```bash
renode -e "i @renode/blinky.resc"
```

Mengamati di GUI Renode (emulasi berjalan tanpa keluar):

```bash
renode -e "i @renode/blinky_gui.resc"
```

Di Monitor Renode, state LED dapat dibaca langsung, misalnya:

```
sysbus.gpioPortD.LED4_Green State
watch "sysbus.gpioPortD.LED4_Green State" 500
```

Debug memakai GDB memakai environment `renode_debug` (bukan default):

```bash
pio debug -e renode_debug --interface=gdb
```

> Environment default tetap `disco_f407vg` untuk board asli
> (`default_envs = disco_f407vg`). Environment `renode_debug` hanya terpakai
> bila dipilih eksplisit, sehingga mahasiswa yang memakai hardware tidak
> terpengaruh.
