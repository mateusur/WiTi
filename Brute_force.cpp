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
 int best_F = INT16_MAX;
 int temp;
void findPermutations(std::vector<parameters> str, int index, size_t n) {
	if (index >= n) {
		temp = calculate_F(str);
		if (temp < best_F) {
			best_F = temp;
		}
		return;
	}
	for (int i = index; i < n; i++) {
		std::swap(str[index], str[i]);
		findPermutations(str, index + 1, n);
		std::swap(str[index], str[i]);
		
	}
}
