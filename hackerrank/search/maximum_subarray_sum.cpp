//
// https://www.hackerrank.com/challenges/maximum-subarray-sum/problem
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <set>
#include <iterator>
using namespace std;

using ivec = vector<long long int>;
using iset = set<long long int>;

tuple<ivec, long long int> read_arr() {
	long long int n, m;
	cin >> n >> m;
	auto arr = ivec(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
		arr[i] %= m;
	}
	return make_tuple(arr, m);
}

template <typename C, typename O>
void copy_all(const C &seq, O &&out) {
	copy(begin(seq), end(seq), out);
}

int main() {
	auto tests = 0;
	cin >> tests;
	auto sums_set = iset();
	for (size_t t = 0; t < tests; ++t) {
		sums_set.clear();
		ivec arr;
		long long int m;
		tie(arr, m) = read_arr();
		auto sums = ivec(arr.size());

		sums[0] = arr[0];
		for (size_t i = 1; i < arr.size(); ++i) {
			sums[i] = (sums[i-1] + arr[i])%m;
		}

		long long int max_sum = 0;

		for (size_t i = 0; i < arr.size(); ++i) {
			max_sum = max(max_sum, sums[i]);

			if (max_sum < sums[i]) {
				max_sum = sums[i];
			}
			if (sums_set.size()) {
				auto min_subsum_iter = sums_set.lower_bound(sums[i]);
				if (min_subsum_iter != sums_set.end()) {
					auto subsum = (sums[i] - *min_subsum_iter)%m;
					if (subsum < 0)
						subsum += m;
					if (max_sum < subsum) {
						max_sum = subsum;
					} else {
					}
				}
				min_subsum_iter = sums_set.begin();
				if (min_subsum_iter != sums_set.end()) {
					auto subsum = (sums[i] - *min_subsum_iter)%m;
					if (subsum < 0)
						subsum += m;
					if (max_sum < subsum) {
						max_sum = subsum;
					}
				}
			}
			sums_set.insert(sums[i]);
		}
		cout << max_sum << endl;
	}

    return 0;
}
