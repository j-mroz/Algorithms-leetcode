//
// https://www.hackerrank.com/challenges/morgan-and-a-string/problem
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <tuple>
#include <cstring>
using namespace std;

using ivec = vector<int>;

struct suffix {
    unsigned pos;
    int rank[2];
};

tuple<ivec, ivec> build_suffix_array(const string &txt) {
    auto size = txt.size();
    auto pos_to_suffix = ivec(size);
    auto suffixes = vector<suffix>(size);

    for (unsigned i = 0; i < size; ++i) {
        suffixes[i] = suffix {i, txt[i]-'a', i+1 < size ? txt[i+1] -'a' : -1};
    }

    auto suffix_cmp = [](const suffix &a, const suffix &b) {
        return (a.rank[0] < b.rank[0]) or
               (a.rank[0] == b.rank[0] and a.rank[1] < b.rank[1]);
    };

    for (auto suffix_len = 2; suffix_len <= size; suffix_len *= 2) {
        sort(suffixes.begin(), suffixes.end(), suffix_cmp);

        auto rank = 0;
        auto prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;

        pos_to_suffix[suffixes[0].pos] = 0;

        for (auto i = 1; i < size; ++i) {
            auto same_as_previous =
                    suffixes[i].rank[0] == prev_rank &&
                    suffixes[i].rank[1] == suffixes[i-1].rank[1];
            prev_rank = suffixes[i].rank[0];
            suffixes[i].rank[0] = same_as_previous ? rank : ++rank;
            pos_to_suffix[suffixes[i].pos] = i;
        }

        for (auto i = 0; i < size; ++i) {
            auto sibling = suffixes[i].pos + suffix_len;
            auto has_sibling = sibling < size;
            suffixes[i].rank[1] = has_sibling ? suffixes[pos_to_suffix[sibling]].rank[0] : -1;
        }
    }
    sort(suffixes.begin(), suffixes.end(), suffix_cmp);

    auto result = ivec();
    result.reserve(size);
    for (auto s : suffixes)
        result.push_back(s.pos);
    return make_tuple(result, pos_to_suffix);
}

int main() {

	auto n = 0;
	cin >> n;

	while (n-- > 0) {
		string first, second;
		cin >> first >> second;

        // Put inpts into one suffix adray, use z as special separator,
        // Knowing the original position of letter we will be able to
        // determine the lexicographicar order of substring starting at given letter
        // from given string.
		first.push_back('z');
		second.push_back('z');
		auto tuple = build_suffix_array(first + second);
		auto order = get<1>(tuple);

		auto f = 0;
		auto s = 0;

		auto fsize = first.size() - 1;
		auto ssize = second.size()- 1  ;

		string output;
		while (f < fsize or s < ssize) {
			if (f < fsize and s < ssize) {
				if (first[f] < second[s]) {
                    // first letter is smaller, take it
					output.push_back(first[f++]);
				} else if (first[f] > second[s]) {
                    // second letter is smaller, take it
					output.push_back(second[s++]);
				} else {
                    // letters are equal, compare their suffix array position
					if (order[f] < order[fsize + 1 + s]) {
						output.push_back(first[f++]);
					} else {
						output.push_back(second[s++]);
					}
				}
			} else if (f < fsize) {
				output.push_back(first[f++]);
			} else if (s < ssize) {
				output.push_back(second[s++]);
			} else {
				assert(0 and "unreachable");
			}
		}
		cout << output;
		if (n != 0)
			cout << endl;
	}


    return 0;
}
