//
// https://www.hackerrank.com/challenges/ashton-and-string/problem
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <cassert>
using namespace std;

using ivec = vector<int>;

struct suffix {
    unsigned pos;
    int rank[2];
};


tuple<ivec, ivec> get_suffix_array(const string &txt) {
    auto size = txt.size();
    auto pos_to_suffix = ivec(size);
    auto suffixes = vector<suffix>(size);

    for (unsigned i = 0; i < size; ++i) {
        suffixes[i] = suffix {i, txt[i], i+1 < size ? txt[i+1] : -1};
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


ivec get_longest_common_prefixes(const string &txt, const ivec &suffix_arr,
								 const ivec &inv_suff_arr) {
    auto n = txt.size();
    auto lcp = ivec(n);

    auto longest = 0;
    for (auto substr = 0; substr < n; ++substr) {
        if (inv_suff_arr[substr] == n - 1) {
            longest = 0;
            continue;
        }
        auto next_substr = suffix_arr[inv_suff_arr[substr] + 1];

        while (substr + longest < n and next_substr + longest < n and
               txt[substr + longest] == txt[next_substr + longest]) {
            longest++;
        }

        lcp[inv_suff_arr[substr]] = longest;

        if (longest > 0)
            longest--;
    }
    return lcp;
}

int main() {

   	auto tests = 0;
   	cin >> tests;

   	string text;
   	for (auto t = 0; t < tests; ++t) {
   		auto text_idx = 0ul;
   		text.clear();
   		cin >> text >> text_idx;

   		ivec suff_arr, inv_suff_arr;
   		tie(suff_arr, inv_suff_arr) = get_suffix_array(text);
   		auto lcp = get_longest_common_prefixes(text, suff_arr, inv_suff_arr);

   		auto len = 0ul;
   		auto suff_idx = 0ul;
   		text_idx;

   		for (suff_idx = 0ul; suff_idx < suff_arr.size(); ++suff_idx) {
   			auto suff_len = text.size() - suff_arr[suff_idx];
   			auto prev_common = suff_idx - 1 < 0 ? 0 : lcp[suff_idx - 1];
   			text_idx += prev_common*(prev_common+1)/2;

   			if (text_idx <= len + suff_len*(suff_len+1)/2) {
   				break;
   			}

   			len += suff_len*(suff_len+1)/2;
   		}
   		text_idx -= len;

   		for (auto idx = 0ul; idx < text.size()-suff_arr[suff_idx]; ++idx) {
   			auto pref_len = idx + 1;
   			if (text_idx <= pref_len) {
   				break;
   			}
   			text_idx -= pref_len;
   		}
   		text_idx--;
   		cout << text[suff_arr[suff_idx] + text_idx] << endl;
   	}

    return 0;
}
