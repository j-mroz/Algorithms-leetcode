//
// https://www.hackerrank.com/challenges/alternating-characters/problem
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int count_deletions(const string& word) {
	int result = 0;
	for (int i = 1; i < word.size(); ++i) {
		if (word[i-1] == word[i])
			++result;
	}
	return result;
}

int main() {

	string word;
	auto n = 0;
    cin >> n;
	while (n-- > 0) {
		cin >> word;
		auto dels = count_deletions(word);
		cout << dels << endl;
	}

    return 0;
}
