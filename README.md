# 🏥 Sistem Manajemen Inventaris Rumah Sakit - SIMIRUS

Program berbasis **CLI (Command Line Interface)** menggunakan **C++** dengan arsitektur **multi-file** untuk mengelola inventaris obat, riwayat transaksi, antrian pasien, sortir, dan navigasi ruangan rumah sakit.

---

## 👥 Anggota Kelompok

| Nama | Peran | Modul |
|------|-------|-------|
| Attahilla Ahmad Willem (250210501044) | Ketua & BST | `obat.h / obat.cpp` |
| Firson Siwan Ta'gan (250210501038) | Integrator & Tampilan | `main.cpp / display.h / display.cpp` |
| Alya Afrilia Iswanty (250210500018) | Linked List | `riwayat.h / riwayat.cpp` |
| Devina Nur Putri Pertiwi (250210500026) | Graph | `graph.h / graph.cpp` |
| Muh. Fathir Alma Arijs (250210501052) | Antrian & Sorting | `antrian.h / antrian.cpp / sortir.h /sortir/cpp`  | 

---

## 📁 Struktur File

```
finals-team5/
├── main.cpp            ← Entry point, menu utama, integrasi semua modul
├── display.h           ← Deklarasi fungsi tampilan CLI
├── display.cpp         ← Implementasi tampilan (header, menu, notifikasi)
├── obat.h              ← Deklarasi struct Obat dan class BSTObat
├── obat.cpp            ← Implementasi BST + binary search + cleanup
├── riwayat.h           ← Deklarasi struct Node dan class Riwayat
├── riwayat.cpp         ← Implementasi linked list + pencarian linear
├── graph.h             ← Deklarasi class Graph
├── graph.cpp           ← Implementasi adjacency list + BFS
├── antrian.h           ← Deklarasi queue pasien
├── antrian.cpp         ← Implementasi queue pasien
├── sortir.h            ← Deklarasi class SortirObat
├── sortir.cpp          ← Implementasi sorting untuk obat
└── README.md
```

---

## 🧠 Implementasi Konsep Struktur Data

### 1. Binary Search Tree (BST) → Stok Obat
Data obat diorganisir dalam **BST** dengan kode obat sebagai key. Traversal **inorder** menghasilkan daftar obat terurut berdasarkan kode.

```
Operasi  : insert() | hapus() | inorder() | tambahStok() | kurangiStok()
File     : obat.h / obat.cpp
```

### 2. Linked List → Riwayat Transaksi
Riwayat transaksi obat dicatat sebagai node dalam **linked list**. Data dapat ditampilkan, dicari, dan dihapus semua.

```
Operasi  : tambah() | tampilkan() | cari() | hapusSemua()
File     : riwayat.h / riwayat.cpp
```

### 3. Queue → Antrian Pasien
Antrian pasien direpresentasikan menggunakan array sirkular. Pasien dapat ditambahkan, dilayani, dan daftar antrian dapat ditampilkan.

```
Operasi  : enqueue() | dequeue() | peek() | tampilkan()
File     : antrian.h / antrian.cpp
```

### 4. Sorting → Urutkan Obat
Obat dapat diurutkan berdasarkan tanggal kadaluarsa menggunakan Insertion Sort dan Merge Sort.

```
Operasi  : insertionSortByKadaluarsa() | mergeSortByKadaluarsa() | tampilkanHasilSort()
File     : sortir.h / sortir.cpp
```

### 5. Graph (Adjacency List) → Navigasi Ruangan
Ruangan rumah sakit direpresentasikan sebagai node dalam **graph**. Koneksi antar-ruangan disimpan dalam **adjacency list** dan jalur terpendek dicari dengan **BFS**.

```
Operasi  : tambahRuangan() | tambahKoneksi() | cariJalur() | tampilkan()
File     : graph.h / graph.cpp
```

### 6. Tampilan CLI
Fungsi tampilan di `display.cpp` menyediakan antarmuka teks untuk menu, header, dan notifikasi.

```
File     : display.h / display.cpp
```

---

## ⚙️ Cara Menjalankan Program

### Prasyarat
- Compiler C++ (g++ versi 11 ke atas)
- Sistem operasi: Windows / Linux / macOS

### Kompilasi Manual

```bash
g++ main.cpp display.cpp obat.cpp riwayat.cpp graph.cpp antrian.cpp sortir.cpp -o simirus -std=c++11
```

### Jalankan Program

```bash
# Linux / macOS
./simirus

# Windows
simirus.exe
```

---

## 🖥️ Fitur Utama Saat Ini

- Kelola Stok Obat (BST)
- Riwayat Transaksi Obat (Linked List)
- Antrian Pasien (Queue)
- Navigasi Ruangan Rumah Sakit (Graph + BFS)
- Urutkan Obat berdasarkan tanggal kadaluarsa
- Validasi input penting untuk stok dan tanggal
- Tampilan CLI interaktif

---

## 📦 Data Demo

Program memuat data awal saat dijalankan:

**Obat:**
| Kode | Nama | Stok | Kadaluarsa |
|------|------|------|------------|
| OBT001 | Paracetamol 500mg | 150 | 2026-12-01 |
| OBT002 | Amoxicillin 250mg | 80 | 2025-08-15 |
| OBT003 | Ibuprofen 400mg | 60 | 2026-03-20 |
| OBT004 | Antasida Tablet | 200 | 2025-11-10 |
| OBT005 | Vitamin C 1000mg | 300 | 2027-01-05 |
| OBT006 | Metformin 500mg | 45 | 2025-06-30 |

**Peta Ruangan:**
- IGD
- Apotek
- Gudang
- Bangsal A
- Bangsal B
- Bangsal C

---

## 📚 Referensi
- Cormen, T. H., et al. *Introduction to Algorithms*. MIT Press.
- Stroustrup, B. *The C++ Programming Language*. Addison-Wesley.
- Materi Kuliah Struktur Data — Semester 2
