#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <iterator>
using namespace std;


using ivec = vector<long long int>;

ivec read_array() {
	auto n = 0ul;
	cin >> n;
	auto arr = ivec(n);
	for (auto i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	return arr;
}

int main() {
	auto arr = read_array();
	sort(arr.begin(), arr.end());

	auto min = UINT_MAX;
	auto mins = vector<int>();
	for (auto pair1 = 0, pair2 = 1; pair2 < arr.size(); ++pair1, ++pair2) {
		auto diff = abs(arr[pair1] - arr[pair2]);
		if (diff < min) {
			min = diff;
			mins.clear();
			mins.push_back(arr[pair1]);
			mins.push_back(arr[pair2]);
		} else if (diff == min) {
			mins.push_back(arr[pair1]);
			mins.push_back(arr[pair2]);
		}
	}

	copy(mins.begin(), mins.end(), ostream_iterator<int>(cout, " "));

    return 0;
}
