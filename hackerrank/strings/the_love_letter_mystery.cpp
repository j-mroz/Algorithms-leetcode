//
// https://www.hackerrank.com/challenges/the-love-letter-mystery/problem
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int get_palindrome_reductions(const string& word) {
	int reductions = 0;

	auto b = 0ul, e = word.size()-1;
	while (b < e) {
		reductions += abs((int)word[b] - (int)word[e]);
		b++; e--;
	}

	return reductions;
}

int main() {
	auto n = 0;
    cin >> n;
	while (n-- > 0) {
		auto word = string();
		cin >> word;
		auto reductions = get_palindrome_reductions(word);
		cout << reductions << endl;
	}

    return 0;
}
