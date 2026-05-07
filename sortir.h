#ifndef SORTIR_H
#define SORTIR_H

#include "obat.h"
#include <vector>
using namespace std;

void insertionSortByKadaluarsa(vector<Obat> &arr);

void mergeSortByKadaluarsa(vector<Obat> &arr, int kiri, int kanan);

void merge(vector<Obat> &arr, int kiri, int tengah, int kanan);

void tampilkanPerbandinganSort(vector<Obat> daftarObat);

void tampilkanHasilSort(const vector<Obat> &arr, const string &judulAlgoritma);

bool tanggalLebihAwal(const string &tglA, const string &tglB);

#endif // SORTIR_H
