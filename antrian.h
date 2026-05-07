#ifndef ANTRIAN_H
#define ANTRIAN_H

#include <string>
using namespace std;

const int MAX_ANTRIAN = 20;

struct Pasien {
    int    nomorAntrian;
    string nama;
    string keperluanObat;
};

struct AntrianPasien {
    Pasien data[MAX_ANTRIAN];
    int    front;
    int    rear;
    int    size;
};

void initAntrian(AntrianPasien &antrian);

bool enqueue(AntrianPasien &antrian, const string &nama, const string &keperluanObat);
bool dequeue(AntrianPasien &antrian, Pasien &pasienKeluar);
bool peek(const AntrianPasien &antrian, Pasien &pasienDepan);

bool isAntrianKosong(const AntrianPasien &antrian);
bool isAntrianPenuh(const AntrianPasien &antrian);
int  jumlahAntrian(const AntrianPasien &antrian);
void tampilkanAntrian(const AntrianPasien &antrian);

#endif // ANTRIAN_H
