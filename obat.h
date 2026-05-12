#ifndef OBAT_H
#define OBAT_H


#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

struct Obat {
    string kode;
    string nama;
    int stok;
    string tanggal_kadaluarsa;
    Obat *left;
    Obat *right;
};

class BSTObat {
private:
    Obat *root;

    Obat *insertRekursif(Obat *node, string kode, string nama, int stok, string exp);
    Obat *cariMin(Obat *node);
    Obat *hapusRekursif(Obat *node, string kode, bool &terhapus);
    Obat *cariNode(Obat *node, string kode);
    void inorderTampil(Obat *node);
    void inorderToArray(Obat *node, vector<Obat> &arr);
    void clear(Obat *node);

public:
    BSTObat();
    ~BSTObat();
    
    bool insert(string kode, string nama, int stok, string exp);
    bool tambahStok(string kode, int jumlah);
    bool kurangiStok(string kode, int jumlah);
    bool hapus(string kode);
    void binarySearch(string kode);
    void tampilkan();
    string getNama(string kode);
    
    vector<Obat> toArray();
};

#endif