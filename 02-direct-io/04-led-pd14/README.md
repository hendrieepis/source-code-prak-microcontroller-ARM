# Modul 02 — Tugas 2: LED LD5 (PD14) Berkedip

## Tujuan

Menyalakan LED LD5 (merah) secara berkedip memakai akses register langsung.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Perangkat | Pin |
|---|---|
| LED LD5 (merah) | PD14 |

## Wiring

Tidak ada rangkaian tambahan.

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

LED LD5 berkedip ±1 detik.

## Troubleshooting

- **LED diam:** pastikan clock GPIOD aktif dan `MODER` PD14 = `01`.
