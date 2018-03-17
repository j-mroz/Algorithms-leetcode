//
// https://www.hackerrank.com/challenges/making-anagrams/problem
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>
using namespace std;

using ivec = vector<int>;

ivec count_character(const string &text) {
	static const int alphabet_size = 'z' - 'a' + 1;
	auto counter = ivec(alphabet_size);

	for (char c : text) {
		++counter[c - 'a'];
	}

	return counter;
}

int main() {
    string key1, key2;
    cin >> key1 >> key2;

    auto key1_counted = count_character(key1);
    auto key2_counted = count_character(key2);

    auto answer = 0;
    for (int i = 0; i < key1_counted.size(); ++i) {
    	answer += abs(key1_counted[i] - key2_counted[i]);
    }

    cout << answer << endl;

    return 0;
}
