# Modul 08 — PWM Software (0,5 s, duty 50%)

## Tujuan

Membuat PWM *software* dengan TIM2: LED dinyalakan pada 0,25 s dan dimatikan
pada 0,5 s menggunakan perbandingan nilai counter.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Konfigurasi timer

- Clock APB1 timer = 16 MHz
- `PSC = 8000 - 1` → tick 0,5 ms
- `ARR = 1000 - 1` → overflow 0,5 s
- LED nyala saat `CNT == 500`, mati saat `CNT == 999` → duty 50%

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| LED | PD12 |

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

LED menyala 0,25 s dan mati 0,25 s (periode 0,5 s, duty 50%).

## Troubleshooting

- **Duty tidak tepat:** periksa nilai pembanding counter dan `ARR`.
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
