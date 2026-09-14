# Modul 02 — Direct IO: Tombol USER (PA0) Mengendalikan LED LD4 (PD12)

## Tujuan

Membaca kondisi tombol pengguna **B1** (terhubung ke pin PA0) dan
menggunakannya untuk menyalakan/mematikan **LED LD4** (terhubung ke pin PD12)
melalui register GPIO secara langsung (*Direct IO*).

## Board target

- Board: **ST STM32F4DISCOVERY**
- ID board PlatformIO: `disco_f407vg`
- Framework: `stm32cube` (header CMSIS `stm32f4xx.h`)

## Kebutuhan perangkat keras

- Board STM32F4Discovery
- Kabel **mini-USB**

## Pin yang dipakai

| Fungsi           | Pin  | Sifat        | Keterangan                     |
|------------------|------|--------------|--------------------------------|
| LED LD4 (hijau)  | PD12 | active-high  | menyala saat HIGH              |
| Tombol B1 (USER) | PA0  | active-high  | bernilai HIGH saat ditekan     |

PA0 dikonfigurasi sebagai masukan (nilai reset `MODER` = 0) dan board sudah
memiliki resistor pull-down, sehingga saat tombol ditekan PA0 bernilai HIGH.

## Wiring

LED dan tombol sudah terpasang di board, sehingga tidak diperlukan rangkaian
tambahan.

![Wiring tombol B1 (PA0) dan LED LD4 (PD12)](assets/wiring.svg)

## Build dan upload

```bash
pio run
pio run -t upload
```

## Program

`src/main.c` — membaca register `GPIOA->IDR` bit 0; jika HIGH, pin PD12
di-*set* (LED menyala), jika LOW, PD12 di-*reset* (LED mati).

## Hasil yang diharapkan

LED LD4 menyala selama tombol B1 ditekan dan mati ketika tombol dilepas.

## Troubleshooting

- **LED tidak merespons tombol:** pastikan `clock` GPIOA diaktifkan
  (`RCC->AHB1ENR` bit 0) karena register `GPIOA->IDR` dibaca.
- **LED terbalik (nyala saat dilepas):** periksa polaritas; pada board ini
  tombol bersifat active-high (ditekan = HIGH).
- **Upload gagal:** periksa kabel mini-USB dan driver ST-LINK.

## Simulasi dengan Renode (tanpa hardware)

Jika board sedang tidak tersedia, firmware dapat diuji pada simulator
**Renode**. Firmware harus sudah dibangun lebih dahulu (`pio run`). Semua
perintah dijalankan dari root project (folder yang berisi `platformio.ini`).

Uji cepat (menjalankan emulasi, mencetak perubahan LED/tombol, lalu keluar):

```bash
renode -e "i @renode/blinky.resc"
```

Mengamati di GUI Renode (emulasi berjalan tanpa keluar):

```bash
renode -e "i @renode/blinky_gui.resc"
```

Di Monitor Renode, state LED dapat dibaca langsung, misalnya:

```
sysbus.gpioPortD.LED4_Green State
watch "sysbus.gpioPortD.LED4_Green State" 500
```

Debug memakai GDB memakai environment `renode_debug` (bukan default):

```bash
pio debug -e renode_debug --interface=gdb
```

> Environment default tetap `disco_f407vg` untuk board asli
> (`default_envs = disco_f407vg`). Environment `renode_debug` hanya terpakai
> bila dipilih eksplisit, sehingga mahasiswa yang memakai hardware tidak
> terpengaruh.
