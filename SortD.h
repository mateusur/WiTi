#pragma once
#include <vector>
#include <string>
#include <fstream>
struct parameters
{
	unsigned int p, w, d, ID;
	//vector<unsigned int> S, C, T;
};

std::vector<parameters> wczytaj(unsigned numer_pliku);
bool compare_d(const parameters& a, const parameters& b);
bool compare_ID(const parameters& a, const parameters& b);
int max(const int& first, const int& second);
int calculate_F(const std::vector<parameters>& dane);