#include "display.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\n  Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void tampilkanSeparator() {
    cout << "  " << string(53, '=') << "\n";
}

void tampilkanHeader(const string &judul) {
    cout << "\n";
    tampilkanSeparator();
    int panjang = 53;
    int sisa = panjang - (int)judul.length();
    int kiri = sisa / 2;
    int kanan = sisa - kiri;
    cout << "  " << string(kiri, ' ') << judul << string(kanan, ' ') << "\n";
    tampilkanSeparator();
    cout << "\n";
}

void tampilkanSuccess(const string &pesan) {
    cout << "\n  [OK] " << pesan << "\n";
}

void tampilkanError(const string &pesan) {
    cout << "\n  [!]  " << pesan << "\n";
}

void tampilkanInfo(const string &pesan) {
    cout << "  -->  " << pesan << "\n";
}

void tampilkanMenuUtama() {
    tampilkanHeader("SISTEM MANAJEMEN INVENTARIS RUMAH SAKIT -- SIMI-RS");
    cout << "  1.  Kelola Stok Obat\n";
    cout << "  2.  Antrian Pasien\n";
    cout << "  3.  Riwayat Transaksi\n";
    cout << "  4.  Urutkan Obat\n";
    cout << "  5.  Navigasi Ruangan\n";
    cout << "  0.  Keluar\n";
    cout << "\n";
    tampilkanSeparator();
    cout << "  Pilihan: ";
}

void tampilkanMenuObat() {
    tampilkanHeader("KELOLA STOK OBAT");
    cout << "  1.  Tambah Obat Baru\n";
    cout << "  2.  Tambah Stok Obat\n";
    cout << "  3.  Kurangi Stok Obat\n";
    cout << "  4.  Hapus Obat\n";
    cout << "  5.  Cari Obat (Binary Search)\n";
    cout << "  6.  Tampilkan Semua Obat\n";
    cout << "  0.  Kembali\n";
    cout << "\n";
    tampilkanSeparator();
    cout << "  Pilihan: ";
}

void tampilkanMenuAntrian() {
    tampilkanHeader("ANTRIAN PASIEN");
    cout << "  1.  Tambah Pasien ke Antrian\n";
    cout << "  2.  Layani Pasien (Dequeue)\n";
    cout << "  3.  Lihat Pasien Terdepan (Peek)\n";
    cout << "  4.  Tampilkan Seluruh Antrian\n";
    cout << "  0.  Kembali\n";
    cout << "\n";
    tampilkanSeparator();
    cout << "  Pilihan: ";
}

void tampilkanMenuRiwayat() {
    tampilkanHeader("RIWAYAT TRANSAKSI");
    cout << "  1.  Tampilkan Seluruh Riwayat\n";
    cout << "  2.  Cari Transaksi by Nama Obat\n";
    cout << "  3.  Lihat Total Transaksi\n";
    cout << "  4.  Hapus Semua Riwayat\n";
    cout << "  0.  Kembali\n";
    cout << "\n";
    tampilkanSeparator();
    cout << "  Pilihan: ";
}

void tampilkanMenuSortir() {
    tampilkanHeader("URUTKAN OBAT BY TANGGAL KADALUARSA");
    cout << "  1.  Insertion Sort\n";
    cout << "  2.  Merge Sort\n";
    cout << "  3.  Bandingkan Kedua Metode\n";
    cout << "  0.  Kembali\n";
    cout << "\n";
    tampilkanSeparator();
    cout << "  Pilihan: ";
}

void tampilkanMenuGraph() {
    tampilkanHeader("NAVIGASI RUANGAN RUMAH SAKIT");
    cout << "  1.  Tampilkan Peta Ruangan\n";
    cout << "  2.  Cari Jalur Antar Ruangan\n";
    cout << "  0.  Kembali\n";
    cout << "\n";
    tampilkanSeparator();
    cout << "  Pilihan: ";
}