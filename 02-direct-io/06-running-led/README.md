# Modul 02 — Tugas 4: Running LED

## Tujuan

Menyalakan LED PD12--PD15 secara bergiliran (running LED) memakai register
`BSRR`.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| LED | Pin |
|---|---|
| LD4 (hijau) | PD12 |
| LD3 (oranye) | PD13 |
| LD5 (merah) | PD14 |
| LD6 (biru) | PD15 |

## Wiring

Tidak ada rangkaian tambahan.

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Satu LED menyala bergiliran dari PD12 sampai PD15 dengan jeda ±0,25 detik.

## Troubleshooting

- **Semua LED menyala:** pastikan LED sebelumnya di-reset sebelum menyalakan
  LED berikutnya.

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
