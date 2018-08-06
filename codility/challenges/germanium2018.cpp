//
// https://app.codility.com/programmers/challenges/germanium2018/
//

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

inline bool contains(int x, unordered_map<int, int> &xs) {
    return xs.count(x) > 0 && xs[x] > 0;
}

inline void flip(int a, int b, unordered_map<int, int> &as,
                 unordered_map<int, int> &bs,
                 unordered_map<int, vector<int>> &b_to_a) {
    as[a]--;
    bs[a]++;
    bs[b]--;
    as[b]++;
}

bool try_flip(int x, int mid, unordered_map<int, int> &as,
              unordered_map<int, int> &bs,
              unordered_map<int, vector<int>> &b_to_a) {

    for (auto a : b_to_a[x]) {

        if (!contains(a, as))
            continue;

        if (a <= mid) {
            if (as[a] > 1) {
                as[a]--;
                bs[x]--;
                return true;
            }
            if (as[a] == 1 && contains(a, bs)) {
                return try_flip(a, mid, as, bs, b_to_a);
            }
        }

        if (a > mid && as[a] > 0) {
            flip(a, x, as, bs, b_to_a);
            return true;
        }
    }
    return false;
}

int solution(vector<int> &A, vector<int> &B) {
    static const size_t buckets = A.size() * 2;

    unordered_map<int, int> as(buckets), bs(buckets);
    unordered_map<int, vector<int>> b_to_a(buckets);

    for (int i = 0; (size_t)i < A.size(); i++) {
        auto a = A[i];
        auto b = B[i];
        as[a]++;
        bs[b]++;
        b_to_a[b].push_back(a);
    }
    for (auto &as : b_to_a) {
        sort(as.second.begin(), as.second.end());
    }

    for (int x = 1; x < A.size() + 1; x++) {
        if (!contains(x, as)) {
            if (contains(x, bs)) {
                if (!try_flip(x, x, as, bs, b_to_a)) {
                    return x;
                }
            } else {
                return x;
            }
        }
    }

    return A.size() + 1;
}
