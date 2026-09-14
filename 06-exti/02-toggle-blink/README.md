# Modul 06 — External Interrupt: Tombol Mengaktifkan/Mematikan Blinky

## Tujuan

Menggunakan EXTI0 (tombol B1/PA0) untuk mengaktifkan atau mematikan blinky LED
secara bergantian.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| LED LD4 | PD12 |
| Tombol B1 (EXTI0) | PA0 |

## Wiring

Semua on-board; lihat `assets/wiring.svg`.

## Build dan upload

```bash
pio run
pio run -t upload
```

## Program

`src/main.c` memakai variabel `volatile` `g_blink`. Di dalam interrupts,
`g_blink` di-toggle. Loop utama mengedipkan LED bila `g_blink` bernilai 1.

## Hasil yang diharapkan

Tekan tombol sekali: LED berkedip. Tekan lagi: LED berhenti (mati).

## Troubleshooting

- **Variabel tidak berubah:** harus `volatile` karena diubah di interrupt.
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
