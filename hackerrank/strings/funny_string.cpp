//
// https://www.hackerrank.com/challenges/funny-string/problem
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool is_funny(const string &word) {
	string rword = word;
	reverse(rword.begin(), rword.end());

	bool funny = true;
	for (int i = 0, j = 1; j < word.size(); ++i, ++j) {
		funny = funny and abs(word[i]-word[j]) == abs(rword[i]-rword[j]);
	}

	return funny;
}

int main() {

	string word;
	auto n = 0;
    cin >> n;
	while (n-- > 0) {
		cin >> word;
		if (is_funny(word)) {
		cout << "Funny" << endl;
		} else {
			cout << "Not Funny" << endl;
		}
	}

    return 0;
}
