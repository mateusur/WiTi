#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;
//wartosci uzywane przy rekurencyjnym brute force
int best_F = INT16_MAX;
int temp;

string names[11] = {
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

struct parameters
{
	unsigned int p, w, d, ID;
	//vector<unsigned int> S, C, T;
};

vector<parameters> wczytaj(unsigned numer_pliku) {
	int n, k;
	vector<parameters> dane;
	ifstream file;
	//file.open("data/data4.txt", ios::out);
	file.open("data/" + names[numer_pliku], ios::out);
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

int calculate_F(const vector<parameters>& dane) {
	auto sumF = 0;
	vector<unsigned int> S, C, T;
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

int opt_permutation(vector<parameters> dane) {
	int best_F = INT16_MAX;
	long long i = 0;
	int temp = 0;
	do {
		temp = calculate_F(dane);
		if (calculate_F(dane) < best_F) best_F = temp;
		//cout << i++ << endl;
	} while (next_permutation(dane.begin(), dane.end(), compare_ID));
	return best_F;
}

bool shouldSwap(vector<parameters> str, int start, int curr) {
	for (int i = start; i < curr; i++) {
		//if (str[i].p == str[curr].p && str[i].w == str[curr].w && str[i].d == str[curr].d)
		if (str[i].ID == str[curr].ID)
			return false;
	}
	return true;
}

void findPermutations(vector<parameters> str, int index, size_t n) {
	if (index >= n) {
		//cout << str[0].ID <<" " << str[1].ID <<" " << str[2].ID << endl;
		//cout << zmienna++ << endl;
		//print(str);
		temp = calculate_F(str);
		if (temp < best_F) {
			best_F = temp;
		}
		return;
	}
	for (int i = index; i < n; i++) {
		// Proceed further for str[i] only if it  
		// doesn't match with any of the characters 
		// after str[index] 
		//bool check = shouldSwap(str, index, i);
		//if (check) {
		swap(str[index], str[i]);
		findPermutations(str, index + 1, n);
		swap(str[index], str[i]);
		//}
	}
}

//sprawdza czy bit 1 jest na danej pozycji
bool sprawdz_bit(int war, int poz) {
	return ((war >> poz) & 1) == 1 ? true : false;
}

//Przesuwa 1 o 'przesuniecie' miejsc w lewo 
int zmien_bit(int liczba, int przesuniecie) {
	liczba &= ~(1 << przesuniecie);
	return liczba;
}

int PD_iteracyjnie(const vector<parameters>& dane) {
	map<int, int> mapa_wartosci;
	mapa_wartosci.insert({0, 0});
	vector<int> temp_sums; // wektor do przechowywania danych o maksymalnych sumach w danej iteracji
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
		mapa_wartosci.insert({d, min});
	}
	/*for(auto k:mapa_wartosci) {
		cout << k.first <<". "<< k.second << endl;
	}*/
	return mapa_wartosci.rbegin()->second;
}

int PD_rekurencyjnie(const vector<parameters>& dane, map<int, int>& mapaF, int szukany_index) {
	vector<int> temp_sums;
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

void przygotuj_mape(map<int, int>& mapa_wartosci, int rozmiar) {
	mapa_wartosci.insert({0, 0});
	for (int i = 1; i < pow(2, rozmiar); i++) {
		mapa_wartosci.insert({i, -1});
	}
}

int main() {
	//for (int f = 0; f < 1; f++) {
	/*	auto start = chrono::steady_clock::now();
		PD_iteracyjnie(dane);
		auto end = chrono::steady_clock::now();
		sredni_czas = chrono::duration_cast<chrono::seconds>(end - start).count();*/
	//	cout << "Czas dla rekurancji:  " << sredni_czas << endl;
	const unsigned max_size = 13;
	int liczony_indeks;
	map<int, int> mapa_wartosci;
	vector<parameters> dane = wczytaj(0);
	int nr = 0;
	int wybor;
	
	cout << endl << "0. Wczytaj dane (aktualnie wczytany rozmiar = " << dane.size() << " )" << endl
		<< "1. Suma F" << endl
		<< "2. Suma F posortowanych danych wg kary" << endl
		<< "3. Brute force iteracyjnie" << endl
		<< "4. Brute force rekurancyjnie" << endl
		<< "5. Programowanie dynamiczne iteracyjnie" << endl
		<< "6. Programowanie dynamiczne rekurencyjnie" << endl
		<< "7. Pokaz menu" << endl
		<< "9. Zakoncz" << endl;
	do {

		cin >> wybor;
		switch (wybor) {
		case 0:
			cout << "Podaj nr. pliku ktory chcesz wpisac (0-10): ";
			cin >> nr;
			dane = wczytaj(nr);
			break;
		case 1:
			cout << "Wynik to: " << calculate_F(dane) << endl;
			break;
		case 2:
			sort(dane.begin(), dane.end(), compare_d);
			cout << "Wynik to: " << calculate_F(dane) << endl;
			break;
		case 3:
			if (dane.size() < max_size) {
				cout << "Licze..." << endl;
				cout << "Wynik to: " << opt_permutation(dane) << endl;
			}
			else {
				cout << "Za duzy rozmiar danych, zmniejsz rozmiar" << endl;
			}
			break;
		case 4:
			if (dane.size() < max_size) {
				cout << "Licze..." << endl;
				findPermutations(dane, 0, dane.size());
				cout << "Wynik to: " << best_F << endl;
			}
			else {
				cout << "Za duzy rozmiar danych, zmniejsz rozmiar" << endl;
			}
			break;
		case 5:
			cout << "Wynik to: " << PD_iteracyjnie(dane) << endl;
			break;
		case 6:
			mapa_wartosci.clear();
			przygotuj_mape(mapa_wartosci, dane.size());
			cout << "rozmiar: " << mapa_wartosci.size() << endl;
			liczony_indeks = pow(2, dane.size()) - 1;
			cout << "Wynik to: " << PD_rekurencyjnie(dane, mapa_wartosci, liczony_indeks) << endl;
			break;
		case 7:
			cout << endl << "0. Wczytaj dane (aktualnie wczytany rozmiar = " << dane.size() << " )" << endl
				<< "1. Suma F" << endl
				<< "2. Suma F posortowanych danych wg kary" << endl
				<< "3. Brute force iteracyjnie" << endl
				<< "4. Brute force rekurancyjnie" << endl
				<< "5. Programowanie dynamiczne iteracyjnie" << endl
				<< "6. Programowanie dynamiczne rekurencyjnie" << endl
				<< "9. Zakoncz" << endl;
			break;
		case 9:
			break;
		default:
			cout << "Nie ma takiej opcji, wybierz cos z dostepnych mozliwosci " << endl;
			break;
		}

	} while (wybor != 9);

	return 0;
}

//int PD(vector<parameters> dane) {
//	vector<int> maxy;
//	// Pierwsze dwa elementy 001 010
//	maxy.push_back(max(dane[0].p - dane[0].d, 0) * dane[0].w);
//	maxy.push_back(max(dane[1].p - dane[1].d, 0) * dane[1].w);
//	// 3 element 0011
//	int temp1 = max(dane[0].p + dane[1].p - dane[0].d, 0) * dane[0].w+ maxy[1];
//	int temp2 = max(dane[0].p + dane[1].p - dane[1].d, 0) * dane[1].w + maxy[0];
//	maxy.push_back(min(temp1, temp2));
//	// 4 element 0100
//	maxy.push_back(max(dane[2].p - dane[2].d, 0) * dane[2].w);
//	// 5 element 0101
//	temp1 = max(dane[0].p + dane[2].p - dane[0].d, 0) * dane[0].w + maxy[3];
//	temp2 = max(dane[0].p + dane[2].p - dane[2].d, 0) * dane[1].w + maxy[0];
//	maxy.push_back(min(temp1, temp2));
//	// 6 element 0110
//	temp1 = max(dane[1].p + dane[2].p - dane[1].d, 0) * dane[1].w + maxy[3];
//	temp2 = max(dane[1].p + dane[2].p - dane[2].d, 0) * dane[2].w + maxy[1];
//	maxy.push_back(min(temp1, temp2));
//	// 7 element 0111
//	temp1 = max(dane[0].p + dane[1].p + dane[2].p - dane[0].d, 0) * dane[0].w + maxy[5];
//	temp2 = max(dane[0].p + dane[1].p + dane[2].p - dane[1].d, 0) * dane[1].w + maxy[4];
//	int temp3 = max(dane[0].p + dane[1].p + dane[2].p - dane[2].d, 0) * dane[2].w + maxy[2];
//	maxy.push_back(min(min(temp1, temp2), temp3));
//	//8 element 1000
//	temp1 = max(dane[3].p - dane[3].d, 0) * dane[3].w + maxy[0];
//	maxy.push_back(temp1);
//	//9 element 1001
//	temp1 = max(dane[0].p + dane[3].p - dane[0].d, 0) * dane[0].w + maxy[7];
//	temp2 = max(dane[0].p + dane[3].p - dane[3].d, 0) * dane[3].w + maxy[0];
//	maxy.push_back(min(temp1, temp2));
//	//10 element 1010
//	temp1 = max(dane[1].p + dane[3].p - dane[1].d, 0) * dane[1].w + maxy[7];
//	temp2 = max(dane[1].p + dane[3].p - dane[3].d, 0) * dane[3].w + maxy[1];
//	maxy.push_back(min(temp1, temp2));
//	//11 element 1011
//	temp1 = max(dane[1].p +dane[2].p+ dane[3].p - dane[0].d, 0) * dane[0].w + maxy[9];
//	temp2 = max(dane[1].p + dane[2].p + dane[3].p - dane[1].d, 0) * dane[1].w + maxy[8];
//	temp3 = max(dane[1].p + dane[2].p + dane[3].p - dane[3].d, 0) * dane[3].w + maxy[2];
//	maxy.push_back(min(min(temp1,temp2),temp3));
//	//12 element 1100
//	temp1 = max( dane[2].p + dane[3].p - dane[2].d, 0) * dane[2].w + maxy[7];
//	temp2 = max(  dane[2].p + dane[3].p - dane[3].d, 0) * dane[3].w + maxy[3];
//	maxy.push_back(min(temp1, temp2));
//	//13 element 1101
//	temp1 = max(dane[0].p + dane[2].p + dane[3].p - dane[0].d, 0) * dane[0].w + maxy[11];
//	temp2 = max(dane[0].p + dane[2].p + dane[3].p - dane[2].d, 0) * dane[2].w + maxy[8];
//	temp3 = max(dane[0].p + dane[2].p + dane[3].p - dane[3].d, 0) * dane[3].w + maxy[5];
//	maxy.push_back(min(min(temp1, temp2), temp3));
//	//14 element 1110
//	temp1 = max(dane[1].p + dane[2].p + dane[3].p - dane[1].d, 0) * dane[1].w + maxy[11];
//	temp2 = max(dane[1].p + dane[2].p + dane[3].p - dane[2].d, 0) * dane[2].w + maxy[9];
//	temp3 = max(dane[1].p + dane[2].p + dane[3].p - dane[3].d, 0) * dane[3].w + maxy[9];
//	maxy.push_back(min(min(temp1, temp2), temp3));
//	//15 element 1111
//	temp1 = max(dane[0].p + dane[1].p + dane[2].p + dane[3].p - dane[0].d, 0) * dane[0].w + maxy[13];
//	temp2 = max(dane[0].p + dane[1].p + dane[2].p + dane[3].p - dane[1].d, 0) * dane[1].w + maxy[12];
//	temp3 = max(dane[0].p + dane[1].p + dane[2].p + dane[3].p - dane[2].d, 0) * dane[2].w + maxy[10];
//int temp4 = max(dane[0].p + dane[1].p + dane[2].p + dane[3].p - dane[3].d, 0) * dane[3].w + maxy[6];
//	maxy.push_back(min(min(temp1, temp2), min(temp3,temp4)));
//	return maxy[14];
//}

//vector<string> kombinacje(string kombinacja) {
//	int count = 0;
//	vector<string> odp;
//	for (int i = 0; i < kombinacja.size(); i++) {
//		if (kombinacja.at(i) == '1') count++;
//	}
//	for (int j = 1; j <= count; j++) {
//		string temp_odp;
//		int temp_count = 0;
//		for (int i = 0; i < kombinacja.size(); i++) {
//			if (kombinacja[i] == '0') temp_odp += "0";
//			else if (kombinacja[i] == '1') {
//				temp_count++;
//				if (temp_count == j) temp_odp += "0";
//				else temp_odp += "1";
//			}
//		}
//		odp.push_back(temp_odp);
//	}
//	return odp;
//}

//bool itob(unsigned liczba, unsigned bit)
//{
//	auto d = 1 << bit;
//	if ((liczba & (d)) > 0) return true;
//	return false;
//}

//int modifyBit(int n, int p, int b)
//{
//	int mask = 1 << p;
//	return (n & ~mask) | ((b << p) & mask);
//}
//int reset(int war, int poz) {
//	return 	(war &= ~(1 << poz));
//};
