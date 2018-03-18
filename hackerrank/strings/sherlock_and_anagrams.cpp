//
// https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <tuple>
#include <set>
#include <unordered_map>
using namespace std;

using ivec = vector<int>;


size_t count_anagarm_substrs(const string &word) {
    unordered_map<string, int> counter;
    for (auto str_size = 1; str_size < word.size(); ++str_size) {
        for (int i = 0; i < word.size() - str_size + 1; ++i) {
            auto substr = word.substr(i, str_size);
            sort(substr.begin(), substr.end());
            counter[substr]++;
        }
    }
    auto result = 0;
    for (auto &sc : counter) {
        result += sc.second*(sc.second-1)/2;
    }
    return result;
}

int main() {
    auto n = 0;
    cin >> n;

    while (n-- > 0) {
        string word;
        cin >> word;
        cout << count_anagarm_substrs(word) << endl;
    }

    return 0;
}
