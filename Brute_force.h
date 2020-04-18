#pragma once
#include "SortD.h"
#include <algorithm>
int opt_permutation(std::vector<parameters> dane);
bool shouldSwap(std::vector<parameters> str, int start, int curr);
void findPermutations(std::vector<parameters> str, int index, size_t n);