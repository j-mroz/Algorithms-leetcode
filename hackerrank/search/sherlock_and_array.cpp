//
// https://www.hackerrank.com/challenges/sherlock-and-array/problem
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
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

int main() {

	auto tests = 0;
	cin >> tests;

	while (tests-- > 0) {
		auto arr = read_array();
		auto sum = accumulate(arr.begin(), arr.end(), 0);
		auto partial = 0;
		for (auto ai : arr) {
			if (partial == sum - partial - ai) {
				cout << "YES" << endl;
				goto next_loop;
			}
			partial += ai;
		}
		cout << "NO" << endl;
    next_loop:
        continue;
	}


    return 0;
}
