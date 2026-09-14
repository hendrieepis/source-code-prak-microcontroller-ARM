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
