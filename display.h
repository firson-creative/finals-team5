#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
using namespace std;

void clearScreen();
void pauseScreen();
void tampilkanSeparator();

void tampilkanHeader(const string &judul);
void tampilkanSuccess(const string &pesan);
void tampilkanError(const string &pesan);
void tampilkanInfo(const string &pesan);

void tampilkanMenuUtama();
void tampilkanMenuObat();
void tampilkanMenuAntrian();
void tampilkanMenuRiwayat();
void tampilkanMenuSortir();
void tampilkanMenuGraph();

#endif