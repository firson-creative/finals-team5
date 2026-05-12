#ifndef SORTIR_H
#define SORTIR_H

#include "obat.h"
#include <vector>
using namespace std;

class SortirObat {
private:
    bool tanggalLebihAwal(const string &tglA, const string &tglB) const;
    void merge(vector<Obat> &arr, int kiri, int tengah, int kanan);
    void mergeSortHelper(vector<Obat> &arr, int kiri, int kanan);

public:
    void insertionSortByKadaluarsa(vector<Obat> &arr);
    void mergeSortByKadaluarsa(vector<Obat> &arr);
    void tampilkanHasilSort(const vector<Obat> &arr, const string &judulAlgoritma) const;
    void tampilkanPerbandinganSort(vector<Obat> daftarObat);
};

#endif // SORTIR_H
