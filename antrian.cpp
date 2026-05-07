#include "antrian.h"
#include <iostream>
#include <iomanip>
using namespace std;

static int nomorUrut = 1;

void initAntrian(AntrianPasien &antrian) {
    antrian.front = 0;
    antrian.rear  = 0;
    antrian.size  = 0;
}

bool enqueue(AntrianPasien &antrian, const string &nama, const string &keperluanObat) {
    if (isAntrianPenuh(antrian)) {
        cout << "[!] Antrian penuh! Maksimal " << MAX_ANTRIAN << " pasien.\n";
        return false;
    }

    Pasien p;
    p.nomorAntrian  = nomorUrut++;
    p.nama          = nama;
    p.keperluanObat = keperluanObat;

    antrian.data[antrian.rear] = p;
    antrian.rear = (antrian.rear + 1) % MAX_ANTRIAN;
    antrian.size++;

    cout << "[+] Pasien \"" << nama << "\" berhasil masuk antrian. "
         << "Nomor antrian: " << p.nomorAntrian << "\n";
    return true;
}

bool dequeue(AntrianPasien &antrian, Pasien &pasienKeluar) {
    if (isAntrianKosong(antrian)) {
        cout << "[!] Antrian kosong. Tidak ada pasien yang bisa dilayani.\n";
        return false;
    }

    pasienKeluar   = antrian.data[antrian.front];
    antrian.front  = (antrian.front + 1) % MAX_ANTRIAN;
    antrian.size--;

    cout << "[✓] Melayani pasien: \"" << pasienKeluar.nama
         << "\" (No. " << pasienKeluar.nomorAntrian << ")"
         << " — Keperluan: " << pasienKeluar.keperluanObat << "\n";
    return true;
}

bool peek(const AntrianPasien &antrian, Pasien &pasienDepan) {
    if (isAntrianKosong(antrian)) {
        cout << "[!] Antrian kosong.\n";
        return false;
    }

    pasienDepan = antrian.data[antrian.front];
    cout << "[i] Pasien terdepan: \"" << pasienDepan.nama
         << "\" (No. " << pasienDepan.nomorAntrian << ")"
         << " — Keperluan: " << pasienDepan.keperluanObat << "\n";
    return true;
}

bool isAntrianKosong(const AntrianPasien &antrian) {
    return antrian.size == 0;
}

bool isAntrianPenuh(const AntrianPasien &antrian) {
    return antrian.size == MAX_ANTRIAN;
}

int jumlahAntrian(const AntrianPasien &antrian) {
    return antrian.size;
}

void tampilkanAntrian(const AntrianPasien &antrian) {
    cout << "\n╔══════════════════════════════════════════════════════╗\n";
    cout <<   "║            DAFTAR ANTRIAN PASIEN APOTEK             ║\n";
    cout <<   "╠══════╦═══════════════════════╦══════════════════════╣\n";
    cout <<   "║  No  ║  Nama Pasien          ║  Keperluan Obat      ║\n";
    cout <<   "╠══════╬═══════════════════════╬══════════════════════╣\n";

    if (isAntrianKosong(antrian)) {
        cout << "║              Antrian kosong saat ini.               ║\n";
    } else {
        for (int i = 0; i < antrian.size; i++) {
            int idx = (antrian.front + i) % MAX_ANTRIAN;
            const Pasien &p = antrian.data[idx];

            cout << "║ " << setw(4) << left << p.nomorAntrian << " ║ "
                 << setw(21) << left << p.nama << " ║ "
                 << setw(20) << left << p.keperluanObat << " ║\n";
        }
    }

    cout << "╚══════╩═══════════════════════╩══════════════════════╝\n";
    cout << "  Total antrian: " << antrian.size << " / " << MAX_ANTRIAN << " pasien\n\n";
}
