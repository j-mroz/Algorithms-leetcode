//
// https://www.hackerrank.com/challenges/icecream-parlor/problem
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

using ivec = vector<int>;

vector<pair<int, int>> read_arr() {
	int n;
	cin >> n;
	auto arr = vector<pair<int, int>>(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i].first;
		arr[i].second = i;
	}
	return arr;
}

int main() {
	auto tests = 0;
	cin >> tests;
	for (int t = 0; t < tests; ++t) {
		int sum;
		cin >> sum;
		auto arr = read_arr();
		sort(arr.begin(), arr.end());

		for (int i = 0; i < arr.size(); ++i) {
			using ev = pair<int, int>;
			auto cmp = [](const ev& a, const ev& b) {
				return a.first < b.first;
			};
			auto pos = lower_bound(arr.begin() + i + 1, arr.end(),
								   make_pair(sum-arr[i].first, -1),
								   cmp);

			if (pos != arr.end() and pos->first == sum - arr[i].first) {
				int a = min(arr[i].second + 1, pos->second + 1);
				int b = max(arr[i].second + 1, pos->second + 1);
				cout << a << " " << b << endl;
				break;
			}
		}
	}

    return 0;
}
