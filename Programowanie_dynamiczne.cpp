#include "Programowanie_dynamiczne.h"
//sprawdza czy bit 1 jest na danej pozycji
bool sprawdz_bit(int war, int poz) {
	return ((war >> poz) & 1) == 1 ? true : false;
}

//Przesuwa 1 o 'przesuniecie' miejsc w lewo 
int zmien_bit(int liczba, int przesuniecie) {
	liczba &= ~(1 << przesuniecie);
	return liczba;
}

int PD_iteracyjnie(const std::vector<parameters>& dane) {
	std::map<int, int> mapa_wartosci;
	mapa_wartosci.insert({ 0, 0 });
	std::vector<int> temp_sums; // wektor do przechowywania danych o maksymalnych sumach w danej iteracji
	int wielkosc_danych = dane.size();
	//liczmy (2^n)-1 wartosci  
	for (int d = 1; d <= pow(2, wielkosc_danych) - 1; d++) {
		//cout << endl << "Iteracja: " << d << " Wartosc w binarnym: " << bitset<4>(d) << endl;
		//Czyscimy wektor z poprzednich wartosci i ustawiamy na maksymalne wartosci
		temp_sums.clear();
		for (int l = 0; l < wielkosc_danych; l++) {
			temp_sums.push_back(INT16_MAX);
		}
		//Liczymy sume "P" sprawdzajac przy ktorym bicie jest "1"
		unsigned suma_p = 0;
		for (int i = 0; i < wielkosc_danych; i++) {
			if (sprawdz_bit(d, i)) {
				//cout << "Potrzebuje dane[" << i << "].p" << endl;
				suma_p += dane[i].p;
			}
		}
		//Zmieniajac pojedyncze "1" na "0" licze maksymalne wartosci podproblemu
		for (int i = 0; i < wielkosc_danych; i++) {
			if (sprawdz_bit(d, i)) {
				int zmienionny_bit = zmien_bit(d, i);
				//cout << "Wartosc (dziesietnie) po obcieciu " << i + 1 << " zera: "
				//	<< zmienionny_bit << " Binarnie to bedzie: "
				//	<< bitset<4>(zmienionny_bit) << endl;
				//cout << "Suma p= " << suma_p << endl;
				//cout << "Wartosc d= " << dane[i].d << endl;
				int max_temp_sum = ((max(suma_p - dane[i].d, 0)) * dane[i].w) + mapa_wartosci[zmienionny_bit];
				//cout << "Suma " << bitset<4>(zmienionny_bit) << " jest rowna= " << mapa_wartosci[zmienionny_bit] << " + " << some_sum2 << endl;
				//cout << "Suma: " << some_sum << endl;
				temp_sums[i] = max_temp_sum;
			}
		}
		int min = *min_element(temp_sums.begin(), temp_sums.end());
		mapa_wartosci.insert({ d, min });
	}
	/*for(auto k:mapa_wartosci) {
		cout << k.first <<". "<< k.second << endl;
	}*/
	return mapa_wartosci.rbegin()->second;
}

int PD_rekurencyjnie(const std::vector<parameters>& dane, std::map<int, int>& mapaF, int szukany_index) {
	std::vector<int> temp_sums;
	int wielkosc_danych = dane.size();

	temp_sums.clear();
	for (int l = 0; l < wielkosc_danych; l++) {
		temp_sums.push_back(INT16_MAX);
	}

	unsigned suma_p = 0;
	for (int i = 0; i < wielkosc_danych; i++) {
		if (sprawdz_bit(szukany_index, i)) {
			//cout << "Potrzebuje dane[" << i << "].p" << endl;
			suma_p += dane[i].p;
		}
	}

	for (int i = 0; i < wielkosc_danych; i++) {
		if (sprawdz_bit(szukany_index, i)) {
			int zmienionny_bit = zmien_bit(szukany_index, i);
			//cout << "Wartosc (dziesietnie) po obcieciu " << i + 1 << " zera: "
			//	<< zmienionny_bit << " Binarnie to bedzie: "
			//	<< bitset<4>(zmienionny_bit) << endl;
			//cout << "Suma p= " << suma_p << endl;
			//cout << "Wartosc d= " << dane[i].d << endl;
			int currentF = mapaF[zmienionny_bit];
			if (currentF == -1) currentF = PD_rekurencyjnie(dane, mapaF, zmienionny_bit);
			int max_temp_sum = ((max(suma_p - dane[i].d, 0)) * dane[i].w) + currentF;
			//cout << "Suma " << bitset<4>(zmienionny_bit) << " jest rowna= " << mapa_wartosci[zmienionny_bit] << " + " << some_sum2 << endl;
			//cout << "Suma: " << some_sum << endl;
			temp_sums[i] = max_temp_sum;
		}
	}
	int min = *min_element(temp_sums.begin(), temp_sums.end());
	mapaF[szukany_index] = min;
	return min;
}

void przygotuj_mape(std::map<int, int>& mapa_wartosci, int rozmiar) {
	mapa_wartosci.insert({ 0, 0 });
	for (int i = 1; i < pow(2, rozmiar); i++) {
		mapa_wartosci.insert({ i, -1 });
	}
}