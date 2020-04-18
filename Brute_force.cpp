#include "Brute_force.h"


int opt_permutation(std::vector<parameters> dane) {
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

bool shouldSwap(std::vector<parameters> str, int start, int curr) {
	for (int i = start; i < curr; i++) {
		//if (str[i].p == str[curr].p && str[i].w == str[curr].w && str[i].d == str[curr].d)
		if (str[i].ID == str[curr].ID)
			return false;
	}
	return true;
}
 int best_F = INT16_MAX;
 int temp;
void findPermutations(std::vector<parameters> str, int index, size_t n) {
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
		std::swap(str[index], str[i]);
		findPermutations(str, index + 1, n);
		std::swap(str[index], str[i]);
		//}
	}
}
