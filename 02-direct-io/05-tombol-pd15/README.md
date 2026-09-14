# Modul 02 — Tugas 3: Tombol B1 (PA0) Mengendalikan LED LD6 (PD15)

## Tujuan

Menyalakan LED LD6 (biru) selama tombol B1 ditekan, memakai masukan digital
`GPIOA->IDR` dan keluaran `GPIOD->BSRR`.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Perangkat | Pin |
|---|---|
| Tombol B1 | PA0 |
| LED LD6 (biru) | PD15 |

## Wiring

Tidak ada rangkaian tambahan.

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

LED LD6 menyala saat B1 ditekan dan mati saat dilepas.

## Troubleshooting

- **LED terbalik:** pastikan PA0 aktif *high* saat ditekan dan logika
  `if`/`else` tidak tertukar.
