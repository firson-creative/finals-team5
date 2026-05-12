#ifndef GRAPH_H
#define GRAPH_H

#include <string>

const int MAX_RUANGAN = 10;  // kapasitas maksimum node dalam graph

// Node untuk adjacency list (linked list per ruangan)
struct NodeTetangga {
    int idRuangan;
    NodeTetangga* next;
};

// Data satu ruangan (vertex)
struct Ruangan {
    int id;
    std::string nama;
    std::string deskripsi;
};

class Graph {
public:
    Graph();
    ~Graph();

    int tambahRuangan(const std::string& nama);
    void tambahKoneksi(const std::string& namaA, const std::string& namaB);
    void tampilkan() const;
    void tampilkanDaftarRuangan() const;
    bool cariJalur(const std::string& asal, const std::string& tujuan) const;

private:
    Ruangan ruangan[MAX_RUANGAN];
    NodeTetangga* adj[MAX_RUANGAN];
    int jumlahRuangan;

    int getIndexRuangan(const std::string& nama) const;
    void tambahSisiSatuArah(int dari, int ke);
    bool cariJalurBFS(int idAsal, int idTujuan) const;
    void hapusGraph();
};

#endif // GRAPH_H
