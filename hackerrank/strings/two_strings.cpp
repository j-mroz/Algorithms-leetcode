//
// https://www.hackerrank.com/challenges/two-strings/problem
//


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
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


bool have_common_character(string a, string b) {
	auto achars = count_character(a);
	auto bchars = count_character(b);
	for (int i = 0; i < achars.size(); ++i)
		if (achars[i] > 0 and bchars[i] > 0)
			return true;

	return false;
}


int main() {
	auto n = 0;
	cin >> n;
	while (n-- > 0) {
		string word1, word2;
		cin >> word1 >> word2;
		if (have_common_character(word1, word2)) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}

    return 0;
}
