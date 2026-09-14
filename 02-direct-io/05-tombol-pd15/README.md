# Modul 02 — Tugas 3: Tombol B1 (PA0) Mengendalikan LED LD6 (PD15)

## Tujuan

Menyalakan LED LD6 (biru) selama tombol B1 ditekan, memakai masukan digital
`GPIOA->IDR` dan keluaran `GPIOD->BSRR`.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Perangkat | Pin |
|---|---|
| Tombol B1 | PA0 |
| LED LD6 (biru) | PD15 |

## Wiring

Tidak ada rangkaian tambahan.

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

LED LD6 menyala saat B1 ditekan dan mati saat dilepas.

## Troubleshooting

- **LED terbalik:** pastikan PA0 aktif *high* saat ditekan dan logika
  `if`/`else` tidak tertukar.

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
