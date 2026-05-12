#include "riwayat.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

static void cetakHeader() {
    cout << "\n";
    cout << "  ***************************************************************\n";
    cout << "  *           RIWAYAT TRANSAKSI OBAT                            *\n";
    cout << "  ***************************************************************\n";
    cout << "\n";
}

Riwayat::Riwayat() : head(nullptr), total(0) {}
Riwayat::~Riwayat() {
    Node *current = head;
    while (current != nullptr) {
        Node *berikutnya = current->next;
        delete current;
        current = berikutnya;
    }
    head  = nullptr;
    total = 0;
}

void Riwayat::tambah(string namaObat, string jenis, int jumlah, string tanggal, string keterangan) {
    Node *nodeBaru = new Node(namaObat, jenis, jumlah, tanggal, keterangan);
    nodeBaru->next = head;
    head = nodeBaru;
    total++;

}

void Riwayat::tampilkan() const {
    if (head == nullptr) {
        cout << "\n  [!] Belum ada riwayat transaksi. [!]\n";
        return;
    }

    cetakHeader();
    cout << "  +-----+--------------------+---------+---------+--------------+-----------------+\n";
    cout << "  | No  | Nama Obat          | Jenis   | Jumlah  | Tanggal      | Keterangan      |\n";
    cout << "  +-----+--------------------+---------+---------+--------------+-----------------+\n";
    
    Node *current = head;
    int nomor   = 1;

    while (current != nullptr) {
        cout << "  | "
             << left  << setw(4)  << nomor
             << "| "
             << left  << setw(19) << current->namaObat
             << "| "
             << left  << setw(8)  << current->jenis
             << "| "
             << right << setw(6)  << current->jumlah
             << "  | "
             << left  << setw(13) << current->tanggal
             << "| "
             << left  << setw(16) << current->keterangan
             << "|\n";
        cout << "  +-----+--------------------+---------+---------+--------------+-----------------+\n";

        current = current->next;
        nomor++;
    }
    cout << "\n";
    cout << "  Total Transaksi : " << total << " data\n\n";
}

static string toLowerString(const string &text) {
    string lower = text;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

bool Riwayat::cari(const string &namaObat) const {
    if (head == nullptr) {
        cout << "\n  [!] Riwayat kosong. [!]\n";
        return false;
    }

    cout << "\n  [CARI] Nama Obat : \"" << namaObat << "\"\n";
    string needle = toLowerString(namaObat);

    Node* current   = head;
    int   ditemukan = 0;
    int   nomor     = 1;

    while (current != nullptr) {
        string namaObatLower = toLowerString(current->namaObat);
        if (namaObatLower.find(needle) != string::npos) {
            if (ditemukan == 0) {
                cout << "  +-----+---------+---------+--------------+-----------------+\n";
                cout << "  | No  | Jenis   | Jumlah  | Tanggal      | Keterangan      |\n";
                cout << "  +-----+---------+---------+--------------+-----------------+\n";
            }
            ditemukan++;
            cout << "  | "
                 << left  << setw(4)  << nomor
                 << "| "
                 << left  << setw(8)  << current->jenis
                 << "| "
                 << right << setw(6)  << current->jumlah
                 << "  | "
                 << left  << setw(13) << current->tanggal
                 << "| "
                 << left  << setw(16) << current->keterangan
                 << "|\n";
            cout << "  +-----+---------+---------+--------------+-----------------+\n";
            nomor++;
        }
        current = current->next;
    }

    if (ditemukan == 0) {
        cout << "  Tidak ditemukan transaksi untuk obat \"" << namaObat  << "\".\n";
        return false;
    }

    cout << "  Ditemukan " << ditemukan
         << " transaksi untuk obat \"" << namaObat << "\".\n";
    return true;
}

void Riwayat::hapusSemua() {
    Node *current = head;
    while (current != nullptr) {
        Node *berikutnya = current->next;
        delete current;
        current = berikutnya;
    }
    head  = nullptr;
    total = 0;
    cout << " Semua riwayat transaksi telah dihapus.\n";
}

int Riwayat::getTotalTransaksi() const {
    return total;
}