# Modul 07 — Timer: Timer Interrupt (0,5 s)

## Tujuan

Mengedipkan LED PD12 setiap 0,5 detik memakai interrupt update TIM2.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Konfigurasi timer

- Clock APB1 timer = 16 MHz
- `PSC = 8000 - 1` → tick 0,5 ms
- `ARR = 1000 - 1` → overflow 0,5 s
- Update interrupt (`TIM_DIER_UIE`) memanggil `TIM2_IRQHandler()`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| LED (interrupt) | PD12 |
| LED (program utama) | PD13 |

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

PD12 berkedip setiap 0,5 detik; PD13 sebagai penanda program utama tetap jalan.

## Troubleshooting

- **Interrupt tidak jalan:** panggil `NVIC_EnableIRQ(TIM2_IRQn)` dan aktifkan
  `TIM_DIER_UIE`.
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
