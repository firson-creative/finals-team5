#ifndef GRAPH_H
#define GRAPH_H

#include <string>
using namespace std;

const int MAX_RUANGAN = 10;  
struct NodeTetangga {
    int idRuangan;        
    NodeTetangga* next;
};

struct Ruangan {
    int id;
    string nama;
    string deskripsi;
};

struct Graph {
    Ruangan ruangan[MAX_RUANGAN];   
    NodeTetangga* adj[MAX_RUANGAN]; 
    int jumlahRuangan;
};


void initGraph(Graph& g);

int tambahRuangan(Graph& g, const string& nama, const string& deskripsi);

void tambahKoneksi(Graph& g, int idA, int idB);
void tampilkanGraph(const Graph& g);

bool cariJalurBFS(const Graph& g, int idAsal, int idTujuan);

void menuNavigasi(Graph& g);
void hapusGraph(Graph& g);

#endif 