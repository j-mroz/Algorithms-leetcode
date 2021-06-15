#include <iostream>
#include <cassert>

// inclusive
template <typename T>
bool bsearch_first(const T &key, T *array, unsigned b, unsigned e, unsigned &pos) {

	while (b < e) {
		unsigned mid = (b+e)/2;
		if (key <= array[mid]) {
			e = mid;
		} else {
			b = mid+1;
		}
	}

	if (array[b] == key) {
		pos = b;
		return true;
	}
	return false;
}

// inclusive upper bound
template <typename T>
bool bsearch_last(const T &key, T *array, unsigned b, unsigned e, unsigned &pos) {

	while (b < e) {
		unsigned mid = (b+e+1)/2;
		if (key < array[mid]) {
			e = mid-1;
		} else {
			b = mid;
		}
	}

	if (array[e] == key) {
		pos = e;
		return true;
	}
	return false;
}

// find first bigger them
template <typename T>
bool bsearch_greater(const T &key, T *array, unsigned b, unsigned e, unsigned &pos) {
	e++;
	while (b < e) {
		unsigned mid = (b+e)/2;
		if (key < array[mid]) {
			e = mid;
		} else {
			b = mid+1;
		}
	}

	pos = e;
	if (array[e] == key) {
		return true;
	}
	return false;
}

int main() {
	{
		int array[12] = {0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9};
		unsigned lower = 0;
		unsigned upper = 0;
		for (int i = 0; i < 10; ++i) {
			bool found = bsearch_first(i, array, 0, 11-1, lower);
			bsearch_last(i, array, 0, 11-1, upper);
			std::cout << i << " l:" << lower << " u:" << upper << "g:" << std::endl;
		}
	}


	// {
	// 	int array[4] = {1, 1, 1, 1};
	// 	unsigned lower = 0;
	// 	unsigned upper = 0;
	// 	bool found = 0;
	// 	// found = bsearch_first(2, array, 0, 3, lower);
	// 	// found = found && bsearch_last(2, array, 0, 3, upper);
	// 	// std::cout << "f:" << found << " l:" << lower << " u:" << upper << std::endl;
	// 	// upper = bsearch_greater(2, array, 0, 3, lower);
	// 	std::cout << " l:" << lower << " u:" << upper << std::endl;
	// }

}