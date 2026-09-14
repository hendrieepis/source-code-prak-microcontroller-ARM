# Modul 02 — Tugas 1: LED LD3 (PD13) Berkedip

## Tujuan

Menyalakan LED LD3 (oranye) secara berkedip memakai akses register langsung.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Pin yang dipakai

| Perangkat | Pin |
|---|---|
| LED LD3 (oranye) | PD13 |

## Wiring

Tidak ada rangkaian tambahan.

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

LED LD3 berkedip ±1 detik.

## Troubleshooting

- **LED diam:** pastikan clock GPIOD aktif dan `MODER` PD13 = `01`.
