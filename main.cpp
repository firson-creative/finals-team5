#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
#include "display.h"
#include "obat.h"      
#include "antrian.h"   
#include "riwayat.h"   
#include "sortir.h"    
#include "graph.h"
using namespace std;

static string tanggalSaatIni() {
    time_t t = time(nullptr);
    tm* sekarang = localtime(&t);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", sekarang);
    return string(buffer);
}

static bool isValidTanggal(const string &tanggal) {
    if (tanggal.size() != 10 || tanggal[4] != '-' || tanggal[7] != '-') {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(static_cast<unsigned char>(tanggal[i]))) {
            return false;
        }
    }
    int bulan = stoi(tanggal.substr(5, 2));
    int hari  = stoi(tanggal.substr(8, 2));
    if (bulan < 1 || bulan > 12) {
        return false;
    }
    int maxHari = 31;
    if (bulan == 2) maxHari = 29;
    else if (bulan == 4 || bulan == 6 || bulan == 9 || bulan == 11) maxHari = 30;
    return hari >= 1 && hari <= maxHari;
}

void menuObat(BSTObat &bst, Riwayat &riwayat) {
    int pilihan;

    do {
        clearScreen();
        tampilkanMenuObat();
        cin >> pilihan;
        cin.ignore();
        clearScreen();
        string kode, nama, exp;
        int jumlah;

        switch (pilihan) {
            case 1: 
                tampilkanHeader("TAMBAH OBAT BARU");
                cout << "  Kode Obat       : "; getline(cin, kode);
                cout << "  Nama Obat       : "; getline(cin, nama);
                cout << "  Jumlah Stok     : "; cin >> jumlah; cin.ignore();
                cout << "  Tgl. Kadaluarsa : "; getline(cin, exp);

                if (kode.empty() || nama.empty() || jumlah < 0 || !isValidTanggal(exp)) {
                    tampilkanError("Input tidak valid. Pastikan kode, nama, stok >= 0, dan tanggal YYYY-MM-DD.");
                } else {
                    bool baru = bst.insert(kode, nama, jumlah, exp);
                    if (baru) {
                        riwayat.tambah(nama, "MASUK", jumlah, tanggalSaatIni(), "Tambah obat baru");
                        tampilkanSuccess("Obat berhasil ditambahkan ke sistem.");
                    } else {
                        riwayat.tambah(nama, "UPDATE", jumlah, tanggalSaatIni(), "Perbarui data obat");
                        tampilkanInfo("Kode obat sudah ada. Data obat diperbarui.");
                    }
                }
                pauseScreen();
                break;

            case 2: 
                tampilkanHeader("TAMBAH STOK OBAT");
                cout << "  Kode Obat   : "; getline(cin, kode);
                cout << "  Jumlah      : "; cin >> jumlah; cin.ignore();

                if (jumlah <= 0) {
                    tampilkanError("Jumlah harus lebih besar dari 0.");
                } else if (bst.tambahStok(kode, jumlah)) {
                    riwayat.tambah(bst.getNama(kode), "MASUK", jumlah, tanggalSaatIni(), "Tambah stok");
                    tampilkanSuccess("Stok berhasil ditambah.");
                } else {
                    tampilkanError("Kode obat tidak ditemukan atau jumlah tidak valid.");
                }
                pauseScreen();
                break;

            case 3: 
                tampilkanHeader("KURANGI STOK OBAT");
                cout << "  Kode Obat   : "; getline(cin, kode);
                cout << "  Jumlah      : "; cin >> jumlah; cin.ignore();

                if (jumlah <= 0) {
                    tampilkanError("Jumlah harus lebih besar dari 0.");
                } else if (bst.kurangiStok(kode, jumlah)) {
                    riwayat.tambah(bst.getNama(kode), "KELUAR", jumlah, tanggalSaatIni(), "Kurangi stok");
                    tampilkanSuccess("Stok berhasil dikurangi.");
                } else {
                    tampilkanError("Kode obat tidak ditemukan atau stok tidak cukup.");
                }
                pauseScreen();
                break;

            case 4: 
                tampilkanHeader("HAPUS OBAT");
                cout << "  Kode Obat : "; getline(cin, kode);
                nama = bst.getNama(kode);

                if (bst.hapus(kode)) {
                    riwayat.tambah(nama.empty() ? kode : nama, "HAPUS", 0, tanggalSaatIni(), "Hapus obat");
                    tampilkanSuccess("Obat berhasil dihapus.");
                } else {
                    tampilkanError("Kode obat tidak ditemukan.");
                }
                pauseScreen();
                break;

            case 5: 
                tampilkanHeader("CARI OBAT (BINARY SEARCH)");
                cout << "  Kode Obat : "; getline(cin, kode);
                cout << "\n";

                bst.binarySearch(kode);
                pauseScreen();
                break;

            case 6: 
                tampilkanHeader("DAFTAR SEMUA OBAT");
                bst.tampilkan();
                pauseScreen();
                break;

            case 0:
                break;

            default:
                tampilkanError("Pilihan tidak valid. Coba lagi.");
                pauseScreen();
        }

    } while (pilihan != 0);
}

void menuAntrian(AntrianPasien &antrian) {
    int pilihan;

    do {
        clearScreen();
        tampilkanMenuAntrian();
        cin >> pilihan;
        cin.ignore();
        clearScreen();
        string nama;
        string keperluan;

        switch (pilihan) {
            case 1: 
                tampilkanHeader("TAMBAH PASIEN KE ANTRIAN");
                cout << "  Nama Pasien        : "; getline(cin, nama);
                cout << "  Keperluan Obat     : "; getline(cin, keperluan);
                if (antrian.enqueue(nama, keperluan)) {
                    tampilkanSuccess("Pasien berhasil masuk antrian.");
                } else {
                    tampilkanError("Antrian penuh! Maksimal kapasitas tercapai.");
                }
                pauseScreen();
                break;

            case 2: 
                tampilkanHeader("LAYANI PASIEN");

                if (!antrian.isKosong()) {
                    Pasien p;
                    if (antrian.dequeue(p)) {
                        tampilkanSuccess("Pasien dilayani: " + p.nama);
                    }
                } else {
                    tampilkanError("Antrian kosong. Tidak ada pasien.");
                }
                pauseScreen();
                break;

            case 3: 
                tampilkanHeader("PASIEN TERDEPAN");

                if (!antrian.isKosong()) {
                    Pasien p;
                    if (antrian.peek(p)) {
                        tampilkanInfo("Pasien terdepan: " + p.nama);
                    }
                } else {
                    tampilkanError("Antrian kosong.");
                }
                pauseScreen();
                break;

            case 4: 
                tampilkanHeader("SELURUH ANTRIAN PASIEN");
                antrian.tampilkan();
                pauseScreen();
                break;

            case 0:
                break;

            default:
                tampilkanError("Pilihan tidak valid. Coba lagi.");
                pauseScreen();
        }

    } while (pilihan != 0);
}

void menuRiwayat(Riwayat &riwayat) {
    int pilihan;

    do {
        clearScreen();
        tampilkanMenuRiwayat();
        cin >> pilihan;
        cin.ignore();
        clearScreen();
        string keyword;

        switch (pilihan) {
            case 1: 
                tampilkanHeader("SELURUH RIWAYAT TRANSAKSI");
                riwayat.tampilkan();
                pauseScreen();
                break;

            case 2: 
                tampilkanHeader("CARI TRANSAKSI (LINEAR SEARCH)");
                cout << "  Nama Obat : "; getline(cin, keyword);
                cout << "\n";
                riwayat.cari(keyword);
                pauseScreen();
                break;

            case 3:
                tampilkanHeader("TOTAL RIWAYAT TRANSAKSI");
                cout << "  Total riwayat transaksi: " << riwayat.getTotalTransaksi() << " data\n";
                pauseScreen();
                break;

            case 4:
                tampilkanHeader("HAPUS SEMUA RIWAYAT");
                riwayat.hapusSemua();
                pauseScreen();
                break;

            case 0:
                break;

            default:
                tampilkanError("Pilihan tidak valid. Coba lagi.");
                pauseScreen();
        }

    } while (pilihan != 0);
}

void menuSortir(BSTObat &bst) {
    SortirObat sortir;
    int pilihan;

    do {
        clearScreen();
        tampilkanMenuSortir();
        cin >> pilihan;
        cin.ignore();
        clearScreen();

        switch (pilihan) {
            case 1: {
                tampilkanHeader("INSERTION SORT - TANGGAL KADALUARSA");
                vector<Obat> arr = bst.toArray();
                sortir.insertionSortByKadaluarsa(arr);
                sortir.tampilkanHasilSort(arr, "INSERTION SORT  [O(n^2)]");
                pauseScreen();
                break;
            }

            case 2: {
                tampilkanHeader("MERGE SORT - TANGGAL KADALUARSA");
                vector<Obat> arr = bst.toArray();
                sortir.mergeSortByKadaluarsa(arr);
                sortir.tampilkanHasilSort(arr, "MERGE SORT      [O(n log n)]");
                pauseScreen();
                break;
            }

            case 3:
                tampilkanHeader("PERBANDINGAN INSERTION SORT vs MERGE SORT");
                sortir.tampilkanPerbandinganSort(bst.toArray());
                pauseScreen();
                break;

            case 0:
                break;

            default:
                tampilkanError("Pilihan tidak valid. Coba lagi.");
                pauseScreen();
        }

    } while (pilihan != 0);
}

void menuGraph(Graph &graph) {
    int pilihan;

    do {
        clearScreen();
        tampilkanMenuGraph();
        cin >> pilihan;
        cin.ignore();
        clearScreen();
        string asal, tujuan;

        switch (pilihan) {
            case 1:
                tampilkanHeader("PETA RUANGAN RUMAH SAKIT");
                graph.tampilkan();
                pauseScreen();
                break;

            case 2:
                tampilkanHeader("CARI JALUR ANTAR RUANGAN (BFS)");
                graph.tampilkanDaftarRuangan();
                cout << "\n  Ruangan Asal   : "; getline(cin, asal);
                cout << "  Ruangan Tujuan : "; getline(cin, tujuan);
                cout << "\n";
                graph.cariJalur(asal, tujuan);
                pauseScreen();
                break;
                
            case 0:
                break;

            default:
                tampilkanError("Pilihan tidak valid. Coba lagi.");
                pauseScreen();
        }

    } while (pilihan != 0);
}

void initDemo(BSTObat &bst, AntrianPasien &antrian, Graph &graph) {

    bst.insert("OBT001", "Paracetamol 500mg", 150, "2026-12-01");
    bst.insert("OBT002", "Amoxicillin 250mg", 80, "2025-08-15");
    bst.insert("OBT003", "Ibuprofen 400mg", 60, "2026-03-20");
    bst.insert("OBT004", "Antasida Tablet", 200, "2025-11-10");
    bst.insert("OBT005", "Vitamin C 1000mg", 300, "2027-01-05");
    bst.insert("OBT006", "Metformin 500mg", 45, "2025-06-30");

    antrian.enqueue("Budi Santoso", "Paracetamol");
    antrian.enqueue("Siti Rahayu", "Amoxicillin");
    antrian.enqueue("Ahmad Fauzi", "Ibuprofen");

    graph.tambahRuangan("IGD");
    graph.tambahRuangan("Apotek");
    graph.tambahRuangan("Gudang");
    graph.tambahRuangan("Bangsal A");
    graph.tambahRuangan("Bangsal B");
    graph.tambahRuangan("Bangsal C");
    graph.tambahKoneksi("IGD", "Apotek");
    graph.tambahKoneksi("IGD", "Bangsal A");
    graph.tambahKoneksi("Apotek", "Gudang");
    graph.tambahKoneksi("Apotek", "Bangsal B");
    graph.tambahKoneksi("Bangsal A", "Bangsal B");
    graph.tambahKoneksi("Bangsal B", "Bangsal C");
    graph.tambahKoneksi("Gudang", "Bangsal C");
}

int main() {
    BSTObat bst;
    AntrianPasien antrian;
    Riwayat riwayat;
    Graph graph;

    initDemo(bst, antrian, graph);
    int pilihan;

    do {
        clearScreen();
        tampilkanMenuUtama();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: menuObat(bst, riwayat); break;
            case 2: menuAntrian(antrian); break;
            case 3: menuRiwayat(riwayat); break;
            case 4: menuSortir(bst); break;
            case 5: menuGraph(graph); break;
            case 0:
                clearScreen();
                tampilkanHeader("TERIMA KASIH");
                cout << "  Program selesai digunakan.\n\n";
                break;
            default:
                tampilkanError("Pilihan tidak valid. Masukkan angka 0-5.");
        }

    } while (pilihan != 0);
    return 0;

}









