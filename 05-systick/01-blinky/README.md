# Modul 05 — SysTick: Blinky LED via Interrupt

## Tujuan

Membuat LED PD12–PD15 berkedip menggunakan interrupt SysTick (berbasis CMSIS),
tanpa SPL.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube` (CMSIS)

## Kebutuhan perangkat keras

- Board STM32F4Discovery
- Kabel **mini-USB**

## Pin yang dipakai

| Fungsi | Pin | Sifat |
|---|---|---|
| LED LD4 | PD12 | active-high |
| LED LD3 | PD13 | active-high |
| LED LD5 | PD14 | active-high |
| LED LD6 | PD15 | active-high |

## Wiring

LED sudah terpasang di board.

![Wiring keempat LED PD12–PD15](assets/wiring.svg)

## Build dan upload

```bash
pio run
pio run -t upload
```

## Program

`src/main.c` mengonfigurasi `SysTick_Config(SystemCoreClock / 1000)` (interupsi
1 ms) dan membalik kondisi LED di dalam `SysTick_Handler()`.

## Hasil yang diharapkan

LED berkedip dengan frekuensi pembalikan 500 Hz (dapat diamati dengan
osilokop).

## Troubleshooting

- **LED tidak berubah:** pastikan `SysTick_Handler()` terdefinisi dan
  `SysTick_Config()` dipanggil.
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
