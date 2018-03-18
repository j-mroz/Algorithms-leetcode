//
// https://www.hackerrank.com/challenges/missing-numbers/problem
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

using ivec = vector<int>;

ivec read_arr() {
	int n;
	cin >> n;
	auto arr = ivec(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	return arr;
}

ivec count_character(const ivec &arr, int min_val, int max_val) {
	auto counter = ivec(max_val - min_val + 1);
	for (int c : arr)
		++counter[c - min_val];
	return counter;
}

int main() {
	auto A = read_arr();
	auto B = read_arr();
	auto counter = count_character(A, 0, 10000);

	for (int i = 0; i < B.size(); ++i) {
		--counter[B[i]];
	}
	for (int i = 0; i < counter.size(); ++i) {
		if (counter[i] < 0) {
			cout << i << " ";
		}
	}


    return 0;
}
