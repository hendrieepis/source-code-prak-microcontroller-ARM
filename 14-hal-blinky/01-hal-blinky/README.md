# Modul 14 — HAL Blinky

## Tujuan

Membuat LED berkedip memakai HAL (Hardware Abstraction Layer): `HAL_Init()`,
`HAL_GPIO_Init()`, `HAL_GPIO_TogglePin()`, dan `HAL_Delay()`.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube` (menyediakan STM32Cube HAL)

## Pin yang dipakai

| Fungsi | Pin |
|---|---|
| LED hijau (LD4) | PD12 |

## Wiring

Tidak ada rangkaian tambahan untuk LED bawaan. Lihat `assets/wiring.svg`.

## Konfigurasi

- `HAL_Init()` menyiapkan SysTick 1 ms
- `HAL_IncTick()` dipanggil dari `SysTick_Handler`

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

LED PD12 berkedip dengan periode 500 ms.

## Troubleshooting

- **`HAL_Delay` menggantung:** pastikan `SysTick_Handler` memanggil
  `HAL_IncTick()`.
- **LED tidak menyala:** periksa `__HAL_RCC_GPIOD_CLK_ENABLE()` dan pin.
