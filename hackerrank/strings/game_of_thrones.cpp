//
// https://www.hackerrank.com/challenges/game-of-thrones/problem
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

bool can_be_anagram_palindrom(const string &txt) {
	static const int alphabet_size = 'z' - 'a' + 1;
	auto counter = ivec(alphabet_size);

	for (char character : txt) {
		if (character >= 'A' and character <= 'Z') {
			assert(0 && "unreachable");
		} else if (character >= 'a' and character <= 'z') {
			++counter[character - 'a'];
		}
	}

	auto is_odd  = [](int v) { return v % 2 == 1; };
	auto odd  = count_if(counter.begin(), counter.end(), is_odd);

	return odd <= 1;
}

int main() {

    string key;
    cin >> key;

    if (can_be_anagram_palindrom(key))
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
