#include <cmath>
#include <cassert>
#include <cstdio>
#include <vector>
#include <iostream>
#include <iterator>
#include <ostream>
#include <algorithm>
#include <tuple>
#include <stack>
using namespace std;

using ivec = vector<int>;

ivec read_array() {
	auto n = 0ul;
	cin >> n;
	auto arr = ivec(n);
	for (auto i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	return arr;
}

size_t mergesort_impl(ivec &arr, int b, int e, ivec& buff) {
	assert(b <= e);
	auto size = e - b;

	auto shifts = 0ull;
	if (size == 1)
		return shifts;

	auto left_begin  = b;
	auto left_end 	 = b + size/2;
	auto left_size	 = left_end - left_begin;
	auto right_begin = b + size/2;
	auto right_end	 = b + size;
	auto right_size  = right_end - right_begin;

	if (left_size > 0)
		shifts += mergesort_impl(arr, left_begin, left_end, buff);
	if (right_size > 0)
		shifts += mergesort_impl(arr, right_begin, right_end, buff);

	auto remaining = size;
	auto left = left_begin;
	auto right = right_begin;
	auto ins = 0;
	while (remaining > 0) {
		if ((left < left_end) and
			(right == right_end or arr[left] <= arr[right])) {
			buff[ins] = arr[left];
			++left;
			++ins;
			--remaining;
		} else if (right < right_end) {
			buff[ins] = arr[right];
			++right;
			++ins;
			--remaining;
			shifts += left_end - left;
		} else {
			assert(0 && "unreachable");
		}
	}
	copy(buff.begin(),
	     buff.begin() + size,
		 arr.begin() + b);
	return shifts;
}


size_t mergesort(ivec &arr) {
	auto buff = ivec(arr.size());
	return mergesort_impl(arr, 0, arr.size(), buff);
}


void run() {
	auto arr = read_array();
	auto shifts = mergesort(arr);
	cout << shifts << endl;
}


int main(int argc, char const *argv[]) {
	int tests = 0;
	cin >> tests;
	while (tests-- > 0) {
		run();
	}
	return 0;
}
