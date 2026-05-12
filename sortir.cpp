#include "sortir.h"
#include <iostream>
#include <iomanip>
using namespace std;

bool SortirObat::tanggalLebihAwal(const string &tglA, const string &tglB) const {
    return tglA < tglB;
}

void SortirObat::insertionSortByKadaluarsa(vector<Obat> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Obat kunci = arr[i];
        int  j     = i - 1;
        while (j >= 0 && tanggalLebihAwal(kunci.tanggal_kadaluarsa,
                                           arr[j].tanggal_kadaluarsa)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = kunci;
    }
}

void SortirObat::merge(vector<Obat> &arr, int kiri, int tengah, int kanan) {
    int n1 = tengah - kiri + 1;
    int n2 = kanan - tengah;

    vector<Obat> L(arr.begin() + kiri,       arr.begin() + kiri + n1);
    vector<Obat> R(arr.begin() + tengah + 1, arr.begin() + tengah + 1 + n2);

    int i = 0, j = 0, k = kiri;
    while (i < n1 && j < n2) {
        if (tanggalLebihAwal(L[i].tanggal_kadaluarsa, R[j].tanggal_kadaluarsa)
            || L[i].tanggal_kadaluarsa == R[j].tanggal_kadaluarsa) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void SortirObat::mergeSortHelper(vector<Obat> &arr, int kiri, int kanan) {
    if (kiri >= kanan) return;
    int tengah = kiri + (kanan - kiri) / 2;
    mergeSortHelper(arr, kiri,      tengah);
    mergeSortHelper(arr, tengah + 1, kanan);
    merge(arr, kiri, tengah, kanan);
}

void SortirObat::mergeSortByKadaluarsa(vector<Obat> &arr) {
    mergeSortHelper(arr, 0, (int)arr.size() - 1);
}

void SortirObat::tampilkanHasilSort(const vector<Obat> &arr, const string &judulAlgoritma) const {
    cout << "\n  [ " << judulAlgoritma << " ]\n";
    cout << "  " << left << setw(10) << "KODE"
         << " | " << setw(20) << "NAMA OBAT"
         << " | " << setw(5)  << "STOK"
         << " | " << "EXP. DATE\n";
    cout << "  " << string(53, '-') << "\n";

    if (arr.empty()) {
        cout << "  [!] Tidak ada data obat.\n";
        return;
    }
    for (const Obat &o : arr) {
        cout << "  " << left << setw(10) << o.kode
             << " | " << setw(20) << o.nama
             << " | " << setw(5)  << o.stok
             << " | " << o.tanggal_kadaluarsa << "\n";
    }
}

void SortirObat::tampilkanPerbandinganSort(vector<Obat> daftarObat) {
    if (daftarObat.empty()) {
        cout << "  [!] Tidak ada data obat untuk diurutkan.\n";
        return;
    }

    vector<Obat> arrInsertion = daftarObat;
    vector<Obat> arrMerge     = daftarObat;

    cout << "\n  ============================================\n";
    cout <<   "   URUTKAN OBAT BERDASARKAN TANGGAL KADALUARSA\n";
    cout <<   "   (Paling dekat kadaluarsa ditampilkan pertama)\n";
    cout <<   "  ============================================\n";

    insertionSortByKadaluarsa(arrInsertion);
    tampilkanHasilSort(arrInsertion, "INSERTION SORT  [O(n^2)]");

    mergeSortByKadaluarsa(arrMerge);
    tampilkanHasilSort(arrMerge, "MERGE SORT      [O(n log n)]");

    cout << "\n  Keterangan:\n";
    cout << "  * Insertion Sort : cocok data kecil, mudah dipahami, in-place.\n";
    cout << "  * Merge Sort     : lebih efisien untuk data besar, butuh memori tambahan.\n";
    cout << "  * Kedua hasil di atas seharusnya identik.\n\n";
}
