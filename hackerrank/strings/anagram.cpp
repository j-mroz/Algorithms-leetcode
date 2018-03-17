//
// https://www.hackerrank.com/challenges/anagram/problem
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


int solve(const string &line) {
	auto line_size = line.size();
	if (line_size % 2 == 1)
		return -1;

	auto word1 = line.substr(0, line_size/2);
	auto word2 = line.substr(line_size/2);
	auto word1_counted = count_character(word1);
	auto word2_counted = count_character(word2);

	auto same_count = 0;
	for (int i = 0; i < word1_counted.size(); ++i) {
		same_count += min(word1_counted[i], word2_counted[i]);
    }

	return word1.size() - same_count;
}


int main() {
	auto n = 0;
	cin >> n;

	while (n-- > 0) {
		string line;
		cin >> line;
		cout << solve(line) << endl;
	}

    return 0;
}
