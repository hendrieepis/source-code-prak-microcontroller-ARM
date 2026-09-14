# Modul 08 — PWM Hardware (TIM4, 1 kHz)

## Tujuan

Membangkitkan PWM *hardware* pada empat kanal TIM4 (PD12–PD15) dengan duty
berbeda (25/75/50/80%).

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Konfigurasi timer

- Clock APB1 timer = 16 MHz
- `PSC = 80 - 1` → tick 5 µs
- `ARR = 200 - 1` → period 1 ms → 1 kHz
- PD12–PD15 sebagai AF2 (TIM4 CH1–CH4)

## Pin yang dipakai

| Kanal | Pin | Duty |
|---|---|---|
| CH1 | PD12 | 25% |
| CH2 | PD13 | 75% |
| CH3 | PD14 | 50% |
| CH4 | PD15 | 80% |

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Empat sinyal PWM 1 kHz dengan duty berbeda pada PD12–PD15 (LED tampak redup
sesuai duty).

## Troubleshooting

- **Tidak ada sinyal:** pastikan pin diatur sebagai alternate function (AF2) dan
  `CCER` mengaktifkan kanal.
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
