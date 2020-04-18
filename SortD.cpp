#include "SortD.h"


std::string names[11] = {
	"data10.txt",
	"data11.txt",
	"data12.txt",
	"data13.txt",
	"data14.txt",
	"data15.txt",
	"data16.txt",
	"data17.txt",
	"data18.txt",
	"data19.txt",
	"data20.txt"
};

std::vector<parameters> wczytaj(unsigned numer_pliku) {
	int n, k;
	std::vector<parameters> dane;
	std::ifstream file;
	//file.open("data/data4.txt", ios::out);
	file.open("data/" + names[numer_pliku], std::ios::out);
	file >> n >> k;
	for (int i = 0; i < n; i++) {
		parameters temp;
		file >> temp.p >> temp.w >> temp.d;
		temp.ID = i + 1;
		dane.push_back(temp);
	}
	file.close();
	return dane;
}

bool compare_d(const parameters& a, const parameters& b) {
	return a.d < b.d;
}

bool compare_ID(const parameters& a, const parameters& b) {
	return a.ID < b.ID;
}

int max(const int& first, const int& second) {
	return first > second ? first : second;
}

int calculate_F(const std::vector<parameters>& dane) {
	auto sumF = 0;
	std::vector<unsigned int> S, C, T;
	S.push_back(0);
	C.push_back(dane[0].p);
	T.push_back(max(C[0] - dane[0].d, 0));
	for (int i = 1; i < dane.size(); i++) {
		S.push_back(C[i - 1]);
		C.push_back(dane[i].p + S[i]);
		T.push_back(max(C[i] - dane[i].d, 0));
	}
	for (int i = 0; i < dane.size(); i++) {
		sumF += dane[i].w * T[i];
	}
	return sumF;
}