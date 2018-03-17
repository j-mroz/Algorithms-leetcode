#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

using ivec = vector<int>;

int main() {

	auto counter = ivec(100);

	auto n = 0ul;
	cin >> n;
	for (auto i = 0; i < n; ++i) {
		int val;
		cin >> val;
		counter[val]++;
	}

	for (auto idx = 0; idx < counter.size(); ++idx) {
		int val = counter[idx];
		while (val--) {
			cout << idx << " ";
		}
	}

    return 0;
}
