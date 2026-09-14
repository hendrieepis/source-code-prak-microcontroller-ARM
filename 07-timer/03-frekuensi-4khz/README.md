# Modul 07 — Tugas: Frekuensi Generator 4 kHz

## Tujuan

Membangkitkan sinyal 4 kHz duty 50% pada pin PD12 memakai TIM2 (polling).

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Konfigurasi timer

- Clock APB1 timer = 16 MHz
- Thigh 125 µs → tick 0,5 µs → `PSC = 8 - 1`
- overflow 125 µs → `ARR = 250 - 1`
- Toggle PD12 setiap overflow → 4 kHz, duty 50%

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| Keluaran sinyal | PD12 |

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Sinyal kotak 4 kHz duty 50% pada PD12.

## Troubleshooting

- **Frekuensi meleset:** periksa nilai `PSC`/`ARR` dan clock timer.
- **Upload gagal:** periksa kabel mini-USB dan driver ST-LINK.

## Simulasi dengan Renode (tanpa hardware)

Jika board sedang tidak tersedia, firmware dapat diuji pada simulator
**Renode**. Firmware harus sudah dibangun lebih dahulu (`pio run`). Semua
perintah dijalankan dari root project (folder yang berisi `platformio.ini`).

```bash
renode -e "i @renode/blinky.resc"        # uji cepat, lalu keluar
renode -e "i @renode/blinky_gui.resc"    # amati di GUI Renode
pio debug -e renode_debug --interface=gdb # debug GDB
```

Di Monitor Renode, state LED dapat dibaca langsung:

```
sysbus.gpioPortD.LED4_Green State
watch "sysbus.gpioPortD.LED4_Green State" 500
```

> Environment default tetap `disco_f407vg` untuk board asli
> (`default_envs = disco_f407vg`). Environment `renode_debug` hanya terpakai
> bila dipilih eksplisit.
