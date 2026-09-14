# Modul 07 — Timer: Timer Polling (1 kHz)

## Tujuan

Membangkitkan sinyal 1 kHz duty 50% pada pin PD12 memakai TIM2 dan pengecekan
flag overflow (polling).

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Konfigurasi timer

- Clock APB1 timer = 16 MHz (HSI)
- `PSC = 80 - 1` → tick 5 µs
- `ARR = 100 - 1` → overflow 500 µs
- Toggle PD12 setiap overflow → 1 kHz, duty 50%

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

Sinyal kotak 1 kHz duty 50% pada PD12 (ukur dengan osiloskop/logic analyzer).

## Troubleshooting

- **Frekuensi tidak sesuai:** sesuaikan `PSC`/`ARR` terhadap clock APB1 timer
  yang sebenarnya.
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
