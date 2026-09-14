# Modul 04 — Standard Peripheral Library (Legacy): Output LED (PD12)

## Tujuan

Membuat LED LD4 (PD12) berkedip menggunakan **Standard Peripheral Library (SPL)**,
untuk memahami posisi SPL dibandingkan akses register langsung dan HAL.

## Board target

- Board: **ST STM32F4DISCOVERY**
- ID board PlatformIO: `disco_f407vg`
- Framework: **`spl`** (materi legacy)

## Kebutuhan perangkat keras

- Board STM32F4Discovery
- Kabel **mini-USB**

## Pin yang dipakai

| Fungsi          | Pin  | Sifat       |
|-----------------|------|-------------|
| LED LD4 (hijau) | PD12 | active-high |

## Wiring

LED LD4 sudah terpasang di board.

![Wiring LED LD4 pada PD12](assets/wiring.svg)

## Build dan upload

```bash
pio run
pio run -t upload
```

> Perhatikan: `platformio.ini` memakai `framework = spl`, bukan `stm32cube`.

## Program

`src/main.c` memakai `RCC_AHB1PeriphClockCmd()`, `GPIO_Init()`,
`GPIO_SetBits()`, dan `GPIO_ResetBits()` dari SPL.

## Hasil yang diharapkan

LED LD4 berkedip (nyala/mati bergantian).

## Troubleshooting

- **Fungsi SPL tidak dikenali:** pastikan `framework = spl` pada
  `platformio.ini`.
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
