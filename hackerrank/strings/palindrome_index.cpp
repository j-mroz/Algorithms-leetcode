//
// https://www.hackerrank.com/challenges/palindrome-index/problem
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


bool is_palindrome(const string &txt) {
	auto b = 0ul, e = txt.size()-1;
	while (b < e) {
		if (txt[b] != txt[e])
			return false;
		++b; --e;
	}
	return true;
}

int get_palindrome_spoiler(const string &txt) {
	auto rtxt = txt;
	reverse(rtxt.begin(), rtxt.end());

	int spoiler = -1;
	for (int i = 0; i < txt.size(); ++i) {
		if (txt[i] != rtxt[i]) {
			spoiler = i;
			break;
		}
	}
	rtxt.erase(txt.size() - spoiler - 1, 1);
	if (is_palindrome(rtxt)) {
		return spoiler;
	}
	return txt.size() - spoiler - 1;

}

int main() {

	auto n = 0;
	cin >> n;

	while (n-- > 0) {
		string txt;
		cin >> txt;
		if (is_palindrome(txt)) {
			cout << -1 << endl;
		} else {
			auto spoiler = get_palindrome_spoiler(txt);
			cout << spoiler << endl;
		}
	}

    return 0;
}
