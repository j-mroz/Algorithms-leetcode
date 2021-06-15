#include <cassert>
#include <iostream>


// bool next_permutation_(int *seq, unsigned size, int perm_num) {
// 	assert(size);

// 	static max_perm = 1;
// 	if (perm_num == 0) {
// 		for (int i = 1; i <= size; ++i)
// 			max_perm *= i;
// 	}
// 	acc++;

// 	static unsigned i = 0;
// 	swap(seq[i], seq[i+1]);
// 	++i;
// 	if (i == size) {
// 		++i;

// 	}


// 	// if (acc == 0) {
// 	// 	i = 0, j = 1;
// 	// 	return false;
// 	// }

// 	return true;
// }

template<typename T>
void swap(T &a, T&b) {
	T t = a; 
	a = b; b = t;
}

bool next_permutation_down(int *seq, unsigned size) {
	static int pos = 0;
	if (pos == size-1) {
		pos = 0;
		swap(seq[pos], seq[pos+1]);
		return false;
	}
	swap(seq[pos], seq[pos+1]);
	pos++;
	return true;
}


bool next_permutation_up(int *seq, unsigned size) {
	static int pos = size-1;
	if (pos == 0) {
		pos = size-1;
		swap(seq[pos], seq[pos-1]);
		return false;
	}
	swap(seq[pos], seq[pos-1]);
	pos--;
	return true;
}

bool next_permutation(int *seq, unsigned size) {
	enum Direction {down, up};
	static Direction dir = down;

	static unsigned long long perm_num = 0;
	static unsigned long long max_perm = 1;
	if (perm_num == max_perm) {
		perm_num = 0;
		max_perm = 1;
		return false;
	}

	if (perm_num == 0) {
		for (int i = 1; i <= size; ++i)
			max_perm *= i;
	}
	++perm_num;

	if (dir == down && !next_permutation_down(seq, size))
		dir = up;
	else if (dir == up && !next_permutation_up(seq, size))
		dir = down;

	return true;
}

int main() {
	int V[4] = {1, 2, 3, 4};

	while (next_permutation(V, 4)) {
		for (int i = 0; i < 4; ++i)
			std::cout << V[i] << " ";
		std::cout << std::endl;
	}

	return 0;
}