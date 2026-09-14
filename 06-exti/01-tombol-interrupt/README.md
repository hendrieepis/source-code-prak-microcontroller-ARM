# Modul 06 — External Interrupt: Tombol B1 (PA0) Membalik LED

## Tujuan

Menggunakan interupsi eksternal (EXTI0) dari tombol B1 (PA0) untuk membalik
kondisi keempat LED, dengan pendekatan CMSIS + register (framework `stm32cube`).

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| LED LD4–LD6 | PD12–PD15 |
| Tombol B1 (EXTI0) | PA0 |

## Wiring

Semua on-board; diagram pada `assets/wiring.svg`.

## Build dan upload

```bash
pio run
pio run -t upload
```

## Program

`src/main.c` menghubungkan EXTI0 ke PA0 (`SYSCFG->EXTICR`), mengaktifkan pemicu
rising (`EXTI->RTSR`), dan mengaktifkan `EXTI0_IRQn` pada NVIC. Di dalam
`EXTI0_IRQHandler()` pending bit dibersihkan dan LED di-toggle.

## Hasil yang diharapkan

Setiap kali tombol B1 ditekan, keempat LED berganti kondisi (nyala↔mati).

## Troubleshooting

- **Interupsi tidak jalan:** pastikan clock SYSCFG aktif dan EXTI0 di-*unmask*.
- **Banyak interupsi sekali tekan:** bersihkan `EXTI->PR` di handler.
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
