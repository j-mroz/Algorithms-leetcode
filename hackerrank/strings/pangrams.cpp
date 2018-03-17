//
// https://www.hackerrank.com/challenges/pangrams/problem
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <iterator>
using namespace std;

using ivec = vector<int>;

bool is_pengram(const string &txt) {
	static const int alphabet_size = 'z' - 'a' + 1;
	auto counter = ivec(alphabet_size);

	for (char character : txt) {
		if (character >= 'A' and character <= 'Z') {
			++counter[character - 'A'];
		} else if (character >= 'a' and character <= 'z') {
			++counter[character - 'a'];
		}
	}
	return all_of(counter.begin(), counter.end(), [](int count) {
		return count > 0;
	});
}

int main() {

	string txt;
	getline(cin, txt);

	if (is_pengram(txt)) {
		cout << "pangram" << endl;
	} else {
		cout << "not pangram" << endl;
	}

    return 0;
}
