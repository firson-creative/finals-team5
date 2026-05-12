#include "obat.h"

BSTObat::BSTObat() {
    root = nullptr;
}

BSTObat::~BSTObat() {
    clear(root);
}

void BSTObat::clear(Obat *node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

Obat *BSTObat::insertRekursif(Obat *node, string kode, string nama, int stok, string exp) {
    if (node == nullptr) {
        Obat *nodeBaru = new Obat();
        nodeBaru->kode = kode;
        nodeBaru->nama = nama;
        nodeBaru->stok = stok;
        nodeBaru->tanggal_kadaluarsa = exp;
        nodeBaru->left = nullptr;
        nodeBaru->right = nullptr;
        return nodeBaru;
    }

    if (kode < node->kode) {
        node->left = insertRekursif(node->left, kode, nama, stok, exp);
    } else if (kode > node->kode) {
        node->right = insertRekursif(node->right, kode, nama, stok, exp);
    }
    return node;
}

Obat* BSTObat::cariNode(Obat *node, string kode) {
    if (node == nullptr || node->kode == kode) {
        return node;
    }
    if (kode < node->kode) {
        return cariNode(node->left, kode);
    }
    return cariNode(node->right, kode);
}

Obat* BSTObat::cariMin(Obat *node) {
    Obat *current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Obat* BSTObat::hapusRekursif(Obat *node, string kode, bool &terhapus) {
    if (node == nullptr) return node;

    if (kode < node->kode) {
        node->left = hapusRekursif(node->left, kode, terhapus);
    } else if (kode > node->kode) {
        node->right = hapusRekursif(node->right, kode, terhapus);
    } else {
        terhapus = true;
        if (node->left == nullptr) {
            Obat *temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Obat *temp = node->left;
            delete node;
            return temp;
        }

        Obat *temp = cariMin(node->right);
        node->kode = temp->kode;
        node->nama = temp->nama;
        node->stok = temp->stok;
        node->tanggal_kadaluarsa = temp->tanggal_kadaluarsa;
        node->right = hapusRekursif(node->right, temp->kode, terhapus);
    }
    return node;
}

void BSTObat::inorderTampil(Obat *node) {
    if (node != nullptr) {
        inorderTampil(node->left);
        cout << "  " << left << setw(10) << node->kode 
             << " | " << setw(20) << node->nama 
             << " | " << setw(5) << node->stok 
             << " | " << node->tanggal_kadaluarsa << "\n";
        inorderTampil(node->right);
    }
}

void BSTObat::inorderToArray(Obat *node, vector<Obat> &arr) {
    if (node != nullptr) {
        inorderToArray(node->left, arr);
        arr.push_back(*node);
        inorderToArray(node->right, arr);
    }
}

bool BSTObat::insert(string kode, string nama, int stok, string exp) {
    if (stok < 0) {
        return false;
    }

    Obat *existing = cariNode(root, kode);
    if (existing != nullptr) {
        existing->nama = nama;
        existing->stok = stok;
        existing->tanggal_kadaluarsa = exp;
        return false;
    }

    root = insertRekursif(root, kode, nama, stok, exp);
    return true;
}

bool BSTObat::tambahStok(string kode, int jumlah) {
    if (jumlah <= 0) {
        return false;
    }
    Obat *target = cariNode(root, kode);
    if (target != nullptr) {
        target->stok += jumlah;
        return true;
    }
    return false;
}

bool BSTObat::kurangiStok(string kode, int jumlah) {
    if (jumlah <= 0) {
        return false;
    }
    Obat *target = cariNode(root, kode);
    if (target != nullptr && target->stok >= jumlah) {
        target->stok -= jumlah;
        return true;
    }
    return false;
}

bool BSTObat::hapus(string kode) {
    bool terhapus = false;
    root = hapusRekursif(root, kode, terhapus);
    return terhapus;
}

string BSTObat::getNama(string kode) {
    Obat *target = cariNode(root, kode);
    if (target != nullptr) {
        return target->nama;
    }
    return "Unknown";
}

void BSTObat::tampilkan() {
    if (root == nullptr) {
        cout << "  [!] Data obat masih kosong.\n";
        return;
    }
    cout << "  " << left << setw(10) << "KODE" << " | " 
         << setw(20) << "NAMA OBAT" << " | " 
         << setw(5) << "STOK" << " | " 
         << "EXP. DATE\n";
    cout << "  " << string(53, '-') << "\n";
    inorderTampil(root);
}

vector<Obat> BSTObat::toArray() {
    vector<Obat> arr;
    inorderToArray(root, arr);
    return arr;
}

void BSTObat::binarySearch(string kodeCari) {
    vector<Obat> arr = toArray();
    int leftIdx = 0;
    int rightIdx = arr.size() - 1;
    bool found = false;

    while (leftIdx <= rightIdx) {
        int mid = leftIdx + (rightIdx - leftIdx) / 2;

        if (arr[mid].kode == kodeCari) {
            cout << "\n  [HASIL PENCARIAN]\n";
            cout << "  Kode Obat : " << arr[mid].kode << "\n";
            cout << "  Nama Obat : " << arr[mid].nama << "\n";
            cout << "  Stok      : " << arr[mid].stok << "\n";
            cout << "  Tgl Exp   : " << arr[mid].tanggal_kadaluarsa << "\n";
            found = true;
            break;
        }

        if (arr[mid].kode < kodeCari) {
            leftIdx = mid + 1;
        } else {
            rightIdx = mid - 1;
        }
    }

    if (!found) {
        cout << "\n  [!] Obat dengan kode '" << kodeCari << "' tidak ditemukan dalam sistem.\n";
    }
}