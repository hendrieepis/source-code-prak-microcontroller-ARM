# Modul 12 — Flash Memory: Tulis dan Baca

## Tujuan

Menghapus satu sektor flash, menuliskan data kata demi kata, lalu memverifikasi
hasil pembacaan.

## Board target

- Board: **ST STM32F4DISCOVERY** (`disco_f407vg`)
- Framework: `stm32cube`

## Kebutuhan perangkat keras

- Board STM32F4Discovery + kabel mini-USB (tanpa rangkaian tambahan).

## Konfigurasi

- Sektor uji: **Sector 2** (alamat `0x08008000`, 16 KB)
- Kedalaman program: kata (word, 32-bit), `PSIZE = x32`
- Data uji: `0xABCDEF01`

## Build dan upload

```bash
pio run
pio run -t upload
```

## Hasil yang diharapkan

Delapan kata tertulis di `0x08008000`. Variabel `ok` bernilai 1 bila seluruh
data terbaca sama; amati melalui debugger.

## Troubleshooting

- **Gagal menulis:** pastikan flash sudah di-*unlock* (`KEYR`) dan tidak `BSY`.
- **Data tidak sesuai:** sektor harus dihapus sebelum ditulis ulang.
- **Alamat salah:** jangan menulis di sektor yang memuat program (Sector 0).
