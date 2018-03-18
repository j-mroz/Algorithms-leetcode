//
// https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <iterator>
#include <functional>
using namespace std;

using ivec = vector<int64_t>;
using iimap = map<int, int64_t>;

ivec count_character(const string &text) {
	static const int alphabet_size = 'z' - 'a' + 1;
	auto counter = ivec(alphabet_size);
	for (char c : text) {
		++counter[c - 'a'];
	}
	return counter;
}

iimap get_values_distr_valsibution(const ivec &counter) {
	auto distr_vals = iimap();
	for (int val : counter) {
		if (val != 0)
			++distr_vals[val];
	}
	return distr_vals;
}


int main() {
	string word1;
	cin >> word1;

	auto counter = count_character(word1);
	auto count_distr_vals = get_values_distr_valsibution(counter);

	auto answer = false;
	if (count_distr_vals.size() == 1) {
		answer = true;
	} else if (count_distr_vals.size() == 2) {
        auto distr_keys = ivec();
		auto distr_vals = ivec();
		for (auto &cd : count_distr_vals) {
            distr_keys.push_back(cd.first);
			distr_vals.push_back(cd.second);
		}
        if ((distr_vals[0] == 1) && ((distr_keys[0] == 1) || ( abs(distr_keys[0]-distr_keys[1]) == 1))) {
            answer = true;
        }
        if ((distr_vals[1] == 1) && ((distr_keys[1] == 1) || ( abs(distr_keys[0]-distr_keys[1]) == 1))) {
            answer = true;
        }

	}

	if (answer) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}

    return 0;
}
