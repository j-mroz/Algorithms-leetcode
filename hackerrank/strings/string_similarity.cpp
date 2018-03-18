//
// https://www.hackerrank.com/challenges/string-similarity/problem
//
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

using ivec = vector<int>;

ivec get_longest_common_prefixes(const string &txt, ivec &suffix_arr) {
    auto n = txt.size();
    auto lcp = ivec(n);
    auto suffix_order = ivec(n);

    for (auto i = 0; i < n; ++i)
        suffix_order[suffix_arr[i]] = i;

    auto longest = 0;
    for (auto substr = 0; substr < n; ++substr) {
        if (suffix_order[substr] == n - 1) {
            longest = 0;
            continue;
        }
        auto next_substr = suffix_arr[suffix_order[substr] + 1];


        while (substr + longest < n and next_substr + longest < n and
               txt[substr + longest] == txt[next_substr + longest]) {
            longest++;
        }

        lcp[suffix_order[substr]] = longest;

        if (longest > 0)
            longest--;
    }
    return lcp;
}

struct suffix {
    unsigned pos;
    int rank[2];
};

ivec build_suffix_array(const string &txt) {
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
    return result;
}




long long int get_string_similarity(string &word) {
    auto n = word.size();

    auto suffix_arr = build_suffix_array(word);


    auto lcp = get_longest_common_prefixes(word, suffix_arr);


    int pivot = 0;
    while (suffix_arr[pivot] != 0)
        ++pivot;

    auto result = 0ull;
    result += word.size();

    int start = pivot + 1;
    auto common = lcp[pivot];
    while (start < n and word[suffix_arr[start]] == word[0]) {
        if (lcp[start-1] > 0) {
            common = min(common, lcp[start-1]);
            // cout << "add " << common << endl;
            result += common;
        } else {
            break;
        }
        ++start;
    }

    start = pivot - 1;
    common = lcp[start];
    while (start >= 0 and word[suffix_arr[start]] == word[0]) {
        if (lcp[start] > 0) {
            common = min(common, lcp[start]);
            result += common;
        } else {
            break;
        }
        --start;
    }

    return result;
}

int main() {
    auto tests = 0;
    cin >> tests;
    for (auto i = 0; i < tests; ++i) {
        auto word = string();
        cin >> word;
        auto res = get_string_similarity(word);
        cout << res << endl;
    }

    return 0;
}
