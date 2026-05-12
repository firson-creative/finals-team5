#include "graph.h"
#include <iostream>
#include <queue>

using namespace std;

Graph::Graph() : jumlahRuangan(0) {
    for (int i = 0; i < MAX_RUANGAN; i++) {
        adj[i] = nullptr;
    }
}

Graph::~Graph() {
    hapusGraph();
}

int Graph::getIndexRuangan(const std::string& nama) const {
    for (int i = 0; i < jumlahRuangan; i++) {
        if (ruangan[i].nama == nama) {
            return i;
        }
    }
    return -1;
}

void Graph::tambahSisiSatuArah(int dari, int ke) {
    NodeTetangga* node = new NodeTetangga;
    node->idRuangan = ke;
    node->next = adj[dari];
    adj[dari] = node;
}

int Graph::tambahRuangan(const std::string& nama) {
    if (jumlahRuangan >= MAX_RUANGAN) {
        cout << "[ERROR] Kapasitas ruangan penuh.\n";
        return -1;
    }
    int id = jumlahRuangan;
    ruangan[id].id = id;
    ruangan[id].nama = nama;
    ruangan[id].deskripsi = "";
    adj[id] = nullptr;
    jumlahRuangan++;
    return id;
}

void Graph::tambahKoneksi(const std::string& namaA, const std::string& namaB) {
    int idA = getIndexRuangan(namaA);
    int idB = getIndexRuangan(namaB);
    if (idA < 0 || idB < 0) {
        cout << "[ERROR] Nama ruangan tidak valid.\n";
        return;
    }
    tambahSisiSatuArah(idA, idB);
    tambahSisiSatuArah(idB, idA);
}

void Graph::tampilkan() const {
    cout << "\n";
    cout << "  +==============================================+\n";
    cout << "  |          PETA KONEKSI RUANGAN RUMAH SAKIT   |\n";
    cout << "  +==============================================+\n\n";

    for (int i = 0; i < jumlahRuangan; i++) {
        cout << "  [" << i << "] " << ruangan[i].nama << "\n";
        if (!ruangan[i].deskripsi.empty()) {
            cout << "       (" << ruangan[i].deskripsi << ")\n";
        }
        cout << "       --> Terhubung ke : ";

        NodeTetangga* curr = adj[i];
        if (curr == nullptr) {
            cout << "(tidak ada koneksi)";
        } else {
            bool pertama = true;
            while (curr != nullptr) {
                if (!pertama) cout << ", ";
                cout << ruangan[curr->idRuangan].nama;
                pertama = false;
                curr = curr->next;
            }
        }
        cout << "\n\n";
    }
}

void Graph::tampilkanDaftarRuangan() const {
    cout << "\n  Daftar Ruangan:\n";
    if (jumlahRuangan == 0) {
        cout << "    (Belum ada ruangan terdaftar)\n";
        return;
    }
    for (int i = 0; i < jumlahRuangan; i++) {
        cout << "    [" << i << "] " << ruangan[i].nama << "\n";
    }
}

bool Graph::cariJalur(const std::string& asal, const std::string& tujuan) const {
    int idAsal = getIndexRuangan(asal);
    int idTujuan = getIndexRuangan(tujuan);
    if (idAsal < 0 || idTujuan < 0) {
        cout << "[ERROR] Nama ruangan tidak valid.\n";
        return false;
    }
    return cariJalurBFS(idAsal, idTujuan);
}

bool Graph::cariJalurBFS(int idAsal, int idTujuan) const {
    if (idAsal < 0 || idAsal >= jumlahRuangan ||
        idTujuan < 0 || idTujuan >= jumlahRuangan) {
        cout << "[ERROR] ID ruangan tidak valid.\n";
        return false;
    }

    if (idAsal == idTujuan) {
        cout << "  Anda sudah berada di " << ruangan[idAsal].nama << ".\n";
        return true;
    }

    bool dikunjungi[MAX_RUANGAN] = {false};
    int parent[MAX_RUANGAN];
    for (int i = 0; i < MAX_RUANGAN; i++) parent[i] = -1;

    queue<int> antrian;
    antrian.push(idAsal);
    dikunjungi[idAsal] = true;

    bool ditemukan = false;

    while (!antrian.empty() && !ditemukan) {
        int sekarang = antrian.front();
        antrian.pop();

        NodeTetangga* curr = adj[sekarang];
        while (curr != nullptr) {
            int tetangga = curr->idRuangan;
            if (!dikunjungi[tetangga]) {
                dikunjungi[tetangga] = true;
                parent[tetangga] = sekarang;

                if (tetangga == idTujuan) {
                    ditemukan = true;
                    break;
                }
                antrian.push(tetangga);
            }
            curr = curr->next;
        }
    }

    if (!ditemukan) {
        cout << "\n  [!] Tidak ada jalur dari "
             << ruangan[idAsal].nama << " ke "
             << ruangan[idTujuan].nama << ".\n";
        return false;
    }

    int jalur[MAX_RUANGAN];
    int panjang = 0;
    for (int v = idTujuan; v != -1; v = parent[v]) {
        jalur[panjang++] = v;
    }

    cout << "\n";
    cout << "  +==============================================+\n";
    cout << "  |               JALUR TERCEPAT (BFS)          |\n";
    cout << "  +==============================================+\n\n";
    cout << "  Dari  : " << ruangan[idAsal].nama << "\n";
    cout << "  Ke    : " << ruangan[idTujuan].nama << "\n";
    cout << "  Jarak : " << (panjang - 1) << " langkah\n\n";
    cout << "  Rute  : ";
    for (int i = panjang - 1; i >= 0; i--) {
        cout << ruangan[jalur[i]].nama;
        if (i > 0) cout << "  -->  ";
    }
    cout << "\n\n";
    return true;
}

void Graph::hapusGraph() {
    for (int i = 0; i < jumlahRuangan; i++) {
        NodeTetangga* curr = adj[i];
        while (curr != nullptr) {
            NodeTetangga* temp = curr;
            curr = curr->next;
            delete temp;
        }
        adj[i] = nullptr;
    }
    jumlahRuangan = 0;
}
