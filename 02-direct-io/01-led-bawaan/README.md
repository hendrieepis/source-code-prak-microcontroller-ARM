# Modul 02 — Direct IO: LED Bawaan (LD4 / PD12) Berkedip

## Tujuan

Membuat LED bawaan **LD4** pada board STM32F4Discovery berkedip (nyala sekitar
satu detik, mati sekitar satu detik) dengan menulis register GPIO secara
langsung (*Direct IO*), tanpa pustaka SPL/HAL.

## Board target

- Board: **ST STM32F4DISCOVERY**
- ID board PlatformIO: `disco_f407vg`
- Framework: `stm32cube` (kode memakai header CMSIS `stm32f4xx.h`)

## Kebutuhan perangkat keras

- Board STM32F4Discovery
- Kabel **mini-USB** untuk pemrograman/debugging

## Pin yang dipakai

| Fungsi          | Pin  | Sifat        | Keterangan        |
|-----------------|------|--------------|-------------------|
| LED LD4 (hijau) | PD12 | active-high  | menyala saat HIGH |

## Wiring

LED LD4 sudah terpasang di board, sehingga tidak diperlukan rangkaian
tambahan.

![Wiring LED LD4 pada PD12](assets/wiring.svg)

## Build dan upload

```bash
pio run
pio run -t upload
```

Atau melalui VS Code (ekstensi PlatformIO): pilih environment `disco_f407vg`,
lalu **Build** dan **Upload**.

## Program

`src/main.c` — menyalakan dan mematikan PD12 melalui register `BSRR`, dengan
penunda waktu *busy-wait* yang dihitung dari `CPU_HZ` dan `LOOP_CYCLES`.

## Hasil yang diharapkan

LED LD4 menyala sekitar satu detik, lalu mati sekitar satu detik, dan berulang.

## Troubleshooting

- **Upload gagal:** pastikan kabel mini-USB terpasang dan driver ST-LINK
  terpasang; coba tekan tombol reset board lalu ulangi upload.
- **LED tidak berkedip:** periksa konfigurasi `MODER` (PD12 sebagai output) dan
  nilai tunda `DELAY_1S`.
- **Kedip tidak tepat satu detik:** sesuaikan `LOOP_CYCLES` (perkiraan jumlah
  siklus per putaran `Delay`).

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
