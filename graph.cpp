#include "graph.h"
#include <iostream>
#include <string>
#include <queue>   
using namespace std;


void initGraph(Graph& g) {
    g.jumlahRuangan = 0;
    for (int i = 0; i < MAX_RUANGAN; i++) {
        g.adj[i] = nullptr;
    }
}


int tambahRuangan(Graph& g, const string& nama, const string& deskripsi) {
    if (g.jumlahRuangan >= MAX_RUANGAN) {
        cout << "[ERROR] Kapasitas ruangan penuh.\n";
        return -1;
    }
    int id = g.jumlahRuangan;
    g.ruangan[id].id          = id;
    g.ruangan[id].nama        = nama;
    g.ruangan[id].deskripsi   = deskripsi;
    g.adj[id]                 = nullptr;
    g.jumlahRuangan++;
    return id;
}


static void tambahSisiSatuArah(Graph& g, int dari, int ke) {
    NodeTetangga* node = new NodeTetangga;
    node->idRuangan    = ke;
    node->next         = g.adj[dari];   
    g.adj[dari]        = node;
}


void tambahKoneksi(Graph& g, int idA, int idB) {
    if (idA < 0 || idA >= g.jumlahRuangan ||
        idB < 0 || idB >= g.jumlahRuangan) {
        cout << "[ERROR] ID ruangan tidak valid.\n";
        return;
    }
    tambahSisiSatuArah(g, idA, idB);
    tambahSisiSatuArah(g, idB, idA);
}


void tampilkanGraph(const Graph& g) {
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════╗\n";
    cout << "  ║          PETA KONEKSI RUANGAN RUMAH SAKIT        ║\n";
    cout << "  ╚══════════════════════════════════════════════════╝\n\n";

    for (int i = 0; i < g.jumlahRuangan; i++) {
        cout << "  [" << i << "] " << g.ruangan[i].nama;
        cout << "  (" << g.ruangan[i].deskripsi << ")\n";
        cout << "       └─ Terhubung ke : ";

        NodeTetangga* curr = g.adj[i];
        if (curr == nullptr) {
            cout << "(tidak ada koneksi)";
        } else {
            bool pertama = true;
            while (curr != nullptr) {
                if (!pertama) cout << ", ";
                cout << g.ruangan[curr->idRuangan].nama;
                pertama = false;
                curr = curr->next;
            }
        }
        cout << "\n\n";
    }
}


bool cariJalurBFS(const Graph& g, int idAsal, int idTujuan) {
    if (idAsal < 0 || idAsal >= g.jumlahRuangan ||
        idTujuan < 0 || idTujuan >= g.jumlahRuangan) {
        cout << "[ERROR] ID ruangan tidak valid.\n";
        return false;
    }

    if (idAsal == idTujuan) {
        cout << "  Anda sudah berada di " << g.ruangan[idAsal].nama << ".\n";
        return true;
    }

  
    bool  dikunjungi[MAX_RUANGAN] = {false};
    int   parent[MAX_RUANGAN];
    for (int i = 0; i < MAX_RUANGAN; i++) parent[i] = -1;

    queue<int> antrian;
    antrian.push(idAsal);
    dikunjungi[idAsal] = true;

    bool ditemukan = false;

    while (!antrian.empty() && !ditemukan) {
        int sekarang = antrian.front();
        antrian.pop();

        NodeTetangga* curr = g.adj[sekarang];
        while (curr != nullptr) {
            int tetangga = curr->idRuangan;
            if (!dikunjungi[tetangga]) {
                dikunjungi[tetangga] = true;
                parent[tetangga]     = sekarang;

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
             << g.ruangan[idAsal].nama << " ke "
             << g.ruangan[idTujuan].nama << ".\n";
        return false;
    }

    
    int jalur[MAX_RUANGAN];
    int panjang = 0;
    for (int v = idTujuan; v != -1; v = parent[v]) {
        jalur[panjang++] = v;
    }

   
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════╗\n";
    cout << "  ║               JALUR TERCEPAT (BFS)              ║\n";
    cout << "  ╚══════════════════════════════════════════════════╝\n\n";
    cout << "  Dari  : " << g.ruangan[idAsal].nama   << "\n";
    cout << "  Ke    : " << g.ruangan[idTujuan].nama << "\n";
    cout << "  Jarak : " << (panjang - 1) << " langkah\n\n";
    cout << "  Rute  : ";
    for (int i = panjang - 1; i >= 0; i--) {
        cout << g.ruangan[jalur[i]].nama;
        if (i > 0) cout << "  -->  ";
    }
    cout << "\n\n";
    return true;
}


void menuNavigasi(Graph& g) {
    int pilihan;
    do {
        cout << "\n";
        cout << "  ╔══════════════════════════════════╗\n";
        cout << "  ║       MENU NAVIGASI RUANGAN      ║\n";
        cout << "  ╠══════════════════════════════════╣\n";
        cout << "  ║  1. Tampilkan Peta Koneksi       ║\n";
        cout << "  ║  2. Cari Jalur Antar Ruangan     ║\n";
        cout << "  ║  0. Kembali ke Menu Utama        ║\n";
        cout << "  ╚══════════════════════════════════╝\n";
        cout << "  Pilih: ";
        cin  >> pilihan;

        if (pilihan == 1) {
            tampilkanGraph(g);

        } else if (pilihan == 2) {
            tampilkanGraph(g);

            int asal, tujuan;
            cout << "  Masukkan ID ruangan ASAL    : ";
            cin  >> asal;
            cout << "  Masukkan ID ruangan TUJUAN  : ";
            cin  >> tujuan;

            cariJalurBFS(g, asal, tujuan);

        } else if (pilihan != 0) {
            cout << "  [!] Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);
}


void hapusGraph(Graph& g) {
    for (int i = 0; i < g.jumlahRuangan; i++) {
        NodeTetangga* curr = g.adj[i];
        while (curr != nullptr) {
            NodeTetangga* temp = curr;
            curr = curr->next;
            delete temp;
        }
        g.adj[i] = nullptr;
    }
    g.jumlahRuangan = 0;
}
