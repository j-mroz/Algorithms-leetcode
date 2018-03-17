#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

using ivec = vector<long long int>;

int main() {

	auto counter = ivec(100);

	auto n = 0ul;
	cin >> n;
	for (auto i = 0; i < n; ++i) {
		int val;
		cin >> val;
		counter[val]++;
	}
	copy(counter.begin(), counter.end(), ostream_iterator<int>(cout, " "));

    return 0;
}
