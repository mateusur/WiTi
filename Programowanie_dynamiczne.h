#pragma once
#include <map>
#include <algorithm>
#include "SortD.h"

void przygotuj_mape(std::map<int, int>& mapa_wartosci, int rozmiar);
int zmien_bit(int liczba, int przesuniecie);
bool sprawdz_bit(int war, int poz);
int PD_iteracyjnie(const std::vector<parameters>& dane);
int PD_rekurencyjnie(const std::vector<parameters>& dane, std::map<int, int>& mapaF, int szukany_index);
