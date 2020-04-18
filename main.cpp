#include <algorithm>
#include <iostream>
#include "Brute_force.h"
#include "Programowanie_dynamiczne.h"
#include "SortD.h"

using namespace std;

//wartosci uzywane przy rekurencyjnym brute force
extern int best_F;
extern int temp;

int main() {
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
