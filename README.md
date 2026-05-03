# 🏥 Sistem Manajemen Inventaris Rumah Sakit

DRAF - MASIH PERLU PENGUBAHAN DAN PENYESUAIAN

Program berbasis **CLI (Command Line Interface)** menggunakan **C++** dengan arsitektur **multi-file** untuk mengelola inventaris obat, antrian pasien, riwayat transaksi, dan navigasi antar ruangan rumah sakit.

> Tugas Akhir — Mata Kuliah Struktur Data  
> Program Studi Teknik Komputer | Semester 2

---

## 👥 Anggota Kelompok

| Nama | Peran | Modul |
|------|-------|-------|
| Attahilla Ahmad Willem | Ketua & BST | `obat.h / obat.cpp` |
| Firson Siwan Ta'gan | Integrator & Tampilan | `main.cpp / display.h / display.cpp` |
| Alya Afrilia Iswanty | Linked List | `riwayat.h / riwayat.cpp` |
| Muh. Fathir Alma Arijs | Array Queue & Sorting | `antrian.h / antrian.cpp / sortir.h / sortir.cpp` |
| Devina Nur Putri Pertiwi | Graph | `graph.h / graph.cpp` |

---

## 📁 Struktur File

```
hospital_inventory/
├── main.cpp            ← Entry point, menu utama, integrasi semua modul
├── display.h           ← Deklarasi fungsi tampilan CLI
├── display.cpp         ← Implementasi tampilan (header, menu, notifikasi)
├── obat.h              ← Deklarasi struct Obat dan class BSTObat
├── obat.cpp            ← Implementasi BST + Binary Search
├── antrian.h           ← Deklarasi class AntrianPasien
├── antrian.cpp         ← Implementasi Array Queue (FIFO)
├── riwayat.h           ← Deklarasi struct Node dan class Riwayat
├── riwayat.cpp         ← Implementasi Linked List + Linear Search
├── sortir.h            ← Deklarasi fungsi sorting
├── sortir.cpp          ← Implementasi Insertion Sort & Merge Sort
├── graph.h             ← Deklarasi class Graph
├── graph.cpp           ← Implementasi Adjacency List + BFS
└── README.md
```

---

## 🧠 Implementasi Konsep Struktur Data

### 1. Array → Antrian Pasien
Antrian pasien diimplementasikan menggunakan **array statis** dengan kapasitas tetap. Menggunakan mekanisme **FIFO (First In First Out)** — pasien yang pertama datang, pertama dilayani.

```
Operasi  : enqueue() | dequeue() | peek() | isKosong() | isPenuh()
File     : antrian.h / antrian.cpp
```

### 2. Linked List → Riwayat Transaksi
Setiap transaksi obat (masuk/keluar) dicatat sebagai **node baru** yang ditambahkan di bagian depan linked list (prepend). Linked list dipilih karena jumlah transaksi tidak terbatas dan tidak memerlukan akses acak.

```
Operasi  : tambah() | tampilkan() | cari() | hapusSemua()
File     : riwayat.h / riwayat.cpp
```

### 3. Binary Search Tree (BST) → Stok Obat
Seluruh data obat diorganisir dalam **BST** dengan kode obat sebagai key. Traversal **inorder** otomatis menghasilkan daftar obat yang terurut berdasarkan kode.

```
Operasi  : insert() | hapus() | inorder() | tambahStok() | kurangiStok()
File     : obat.h / obat.cpp
```

### 4. Linear Search → Cari Riwayat
Pencarian transaksi berdasarkan nama obat dilakukan secara **linear** dari node pertama hingga ditemukan. Digunakan pada Linked List yang tidak terurut.

```
Kompleksitas : O(n)
File         : riwayat.h / riwayat.cpp
```

### 5. Binary Search → Cari Kode Obat
BST di-traverse **inorder** terlebih dahulu menghasilkan array terurut, kemudian **binary search** dijalankan untuk mencari kode obat. Demonstrasi nyata mengapa data harus terurut sebelum binary search dapat digunakan.

```
Kompleksitas : O(log n)
File         : obat.h / obat.cpp
```

### 6. Insertion Sort & Merge Sort → Urutkan Kadaluarsa
Array obat hasil inorder BST diurutkan berdasarkan **tanggal kadaluarsa terdekat**. Kedua algoritma diimplementasikan dan dapat dibandingkan hasilnya secara langsung.

```
Insertion Sort  : O(n²)    — cocok untuk data kecil
Merge Sort      : O(n log n) — efisien untuk data besar
File            : sortir.h / sortir.cpp
```

### 7. Graph (Adjacency List) → Navigasi Ruangan
Ruangan-ruangan rumah sakit direpresentasikan sebagai **node** dalam graph. Koneksi antar ruangan yang bertetangga disimpan sebagai **adjacency list**. Pencarian jalur menggunakan **BFS (Breadth-First Search)**.

```
Ruangan  : IGD | Apotek | Gudang | Bangsal A | Bangsal B | Bangsal C
Operasi  : tambahRuangan() | tambahKoneksi() | cariJalur() | tampilkan()
File     : graph.h / graph.cpp
```

---

## ⚙️ Cara Menjalankan Program

### Prasyarat
- Compiler C++ (g++ versi 11 ke atas)
- Sistem operasi: Windows / Linux / macOS

### Kompilasi Manual

```bash
g++ main.cpp display.cpp obat.cpp antrian.cpp riwayat.cpp sortir.cpp graph.cpp -o hospital -std=c++11
```

### Jalankan Program

```bash
# Linux / macOS
./hospital

# Windows
hospital.exe
```

### Menggunakan Makefile *(opsional)*

```bash
make        # kompilasi
make run    # kompilasi + jalankan
make clean  # hapus file hasil kompilasi
```

---

## 🖥️ Tampilan Program

```
  =====================================================
       SISTEM MANAJEMEN INVENTARIS RUMAH SAKIT        
  =====================================================

  1.  Kelola Stok Obat       (BST + Binary Search)
  2.  Antrian Pasien          (Array Queue)
  3.  Riwayat Transaksi       (Linked List + Linear Search)
  4.  Urutkan Obat            (Insertion Sort & Merge Sort)
  5.  Navigasi Ruangan        (Graph BFS)
  0.  Keluar

  =====================================================
  Pilihan: _
```

---

## 📦 Data Demo

Program sudah dilengkapi data awal yang dimuat otomatis saat program dijalankan:

**Obat:**
| Kode | Nama | Stok | Kadaluarsa |
|------|------|------|------------|
| OBT001 | Paracetamol 500mg | 150 | 2026-12-01 |
| OBT002 | Amoxicillin 250mg | 80 | 2025-08-15 |
| OBT003 | Ibuprofen 400mg | 60 | 2026-03-20 |
| OBT004 | Antasida Tablet | 200 | 2025-11-10 |
| OBT005 | Vitamin C 1000mg | 300 | 2027-01-05 |
| OBT006 | Metformin 500mg | 45 | 2025-06-30 |

**Antrian Pasien:** Budi Santoso → Siti Rahayu → Ahmad Fauzi

**Peta Ruangan:**
```
IGD ──── Apotek ──── Gudang
 │          │           │
Bangsal A  Bangsal B  Bangsal C
 └──────────┘    └────────┘
```

---

## 📋 Pembagian Kontribusi

| Nama | Kontribusi Utama |
|------|-----------------|
| Attahilla Ahmad Willem | Struct Obat, BST (insert/delete/inorder), Binary Search pada array |
| Firson Siwan Ta'gan | `main.cpp` (menu loop, sub-menu, integrasi), fungsi tampilan CLI, data demo, README |
| Alya Afrilia Iswanty | Struct Node, Linked List (prepend/traversal), Linear Search, manajemen memori |
| Muh. Fathir Alma Arijs | Array Queue (enqueue/dequeue/peek), Insertion Sort, Merge Sort, perbandingan sort |
| Devina Nur Putri Pertiwi | Graph adjacency list, BFS pencarian jalur, tampilan peta ruangan teks |

---

## 📚 Referensi

- Cormen, T. H., et al. *Introduction to Algorithms*. MIT Press.
- Stroustrup, B. *The C++ Programming Language*. Addison-Wesley.
- Materi Kuliah Struktur Data — Semester 2