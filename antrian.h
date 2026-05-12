#ifndef ANTRIAN_H
#define ANTRIAN_H

#include <string>
using namespace std;

const int MAX_ANTRIAN = 20;

struct Pasien {
    int nomorAntrian;
    string nama;
    string keperluanObat;
};

class AntrianPasien {
private:
    Pasien data[MAX_ANTRIAN];
    int front;
    int rear;
    int size;
    static int nomorUrut;

public:
    AntrianPasien();
    bool enqueue(const string &nama, const string &keperluanObat);
    bool dequeue(Pasien &pasienKeluar);
    bool peek(Pasien &pasienDepan) const;
    bool isKosong() const;
    bool isPenuh() const;
    int jumlah() const;
    void tampilkan() const;
};

#endif // ANTRIAN_H
