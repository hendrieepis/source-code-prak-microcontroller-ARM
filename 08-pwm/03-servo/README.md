# Modul 08 — Tugas: PWM Servo (20 ms, pulse 1,5 ms)

## Tujuan

Membangkitkan sinyal kontrol servo: periode 20 ms dengan lebar pulsa 1,5 ms
(posisi tengah) memakai TIM4 CH1 (PD12).

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Konfigurasi timer

- Clock APB1 timer = 16 MHz
- `PSC = 160 - 1` → tick 10 µs
- `ARR = 2000 - 1` → period 20 ms (50 Hz)
- `CCR1 = 150` → pulse 1,5 ms

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| Sinyal PWM servo | PD12 |

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Sinyal PWM 50 Hz dengan lebar pulsa 1,5 ms pada PD12.

## Troubleshooting

- **Pulsa tidak sesuai:** periksa `PSC`/`ARR`/`CCR1` terhadap clock timer.
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
