#ifndef RIWAYAT_H
#define RIWAYAT_H
#include <string>
using namespace std;

struct Node {
    string namaObat;    
    string jenis;       
    int jumlah;      
    string tanggal;     
    string keterangan;  
    Node *next;        

    Node(string namaObat, string jenis, int jumlah,
         string tanggal, string keterangan = "")
        : namaObat(namaObat), jenis(jenis), jumlah(jumlah),
          tanggal(tanggal), keterangan(keterangan), next(nullptr) {}
};

class Riwayat {
private:
    Node *head;     
    int total;   

public:
    Riwayat();
    ~Riwayat();
    void tambah(string namaObat, string jenis, int jumlah, string tanggal, string keterangan = "");
    void tampilkan() const;
    bool cari(const string &namaObat) const;
    void hapusSemua();
    int getTotalTransaksi() const;
};

#endif 