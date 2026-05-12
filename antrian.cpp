#include "antrian.h"
#include <iostream>
#include <iomanip>
using namespace std;

int AntrianPasien::nomorUrut = 1;

AntrianPasien::AntrianPasien() : front(0), rear(0), size(0) {}

bool AntrianPasien::enqueue(const string &nama, const string &keperluanObat) {
    if (isPenuh()) {
        return false;
    }

    Pasien p;
    p.nomorAntrian  = nomorUrut++;
    p.nama          = nama;
    p.keperluanObat = keperluanObat;

    data[rear] = p;
    rear = (rear + 1) % MAX_ANTRIAN;
    size++;
    return true;
}

bool AntrianPasien::dequeue(Pasien &pasienKeluar) {
    if (isKosong()) {
        return false;
    }

    pasienKeluar   = data[front];
    front  = (front + 1) % MAX_ANTRIAN;
    size--;
    return true;
}

bool AntrianPasien::peek(Pasien &pasienDepan) const {
    if (isKosong()) {
        return false;
    }

    pasienDepan = data[front];
    return true;
}

bool AntrianPasien::isKosong() const {
    return size == 0;
}

bool AntrianPasien::isPenuh() const {
    return size == MAX_ANTRIAN;
}

int AntrianPasien::jumlah() const {
    return size;
}

void AntrianPasien::tampilkan() const {
    cout << "\n+======================================================+\n";
    cout <<   "|            DAFTAR ANTRIAN PASIEN APOTEK             |\n";
    cout <<   "+======+=====================+======================+\n";
    cout <<   "|  No  |  Nama Pasien          |  Keperluan Obat      |\n";
    cout <<   "+======+=====================+======================+\n";

    if (isKosong()) {
        cout << "|              Antrian kosong saat ini.               |\n";
    } else {
        for (int i = 0; i < size; i++) {
            int idx = (front + i) % MAX_ANTRIAN;
            const Pasien &p = data[idx];

            cout << "| " << setw(4) << left << p.nomorAntrian << " | "
                 << setw(21) << left << p.nama << " | "
                 << setw(20) << left << p.keperluanObat << " |\n";
        }
    }

    cout << "+======+=====================+======================+\n";
    cout << "  Total antrian: " << size << " / " << MAX_ANTRIAN << " pasien\n\n";
}
