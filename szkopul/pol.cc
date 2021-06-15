#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct Enumerated {
    size_t index;
    T value;
};

template <typename Q, typename T>
inline void enqueue_non_increasing(Q &q, Enumerated<T> x) {
    while (!q.empty() && q.back().value < x.value) {
        q.pop_back();
    }
    q.push_back(x);
}

template <typename Q, typename T>
inline void enqueue_non_decreasing(Q &q, Enumerated<T> x) {
    while (!q.empty() && q.back().value > x.value) {
        q.pop_back();
    }
    q.push_back(x);
}

template <typename Q, typename T>
inline void dequeue_until_index(Q &q, size_t index) {
    while (!q.empty() && q.front().index < index) {
        q.pop_front();
    }
}

template <typename Q, typename T>
uint64_t compute(Q &lq, Q &rq, const T &min_value_diff, size_t window_start) {
    dequeue_until_index<Q, T>(lq, window_start);
    dequeue_until_index<Q, T>(rq, window_start);

    uint64_t result = 0;
    auto lmax = lq.front();
    auto rmax = rq.front();
    if (rmax.value - lmax.value >= min_value_diff) {
        result = 1 + rmax.value - lmax.value - min_value_diff;
    }
    return result;
}

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    uint64_t result = 0;
    deque<Enumerated<int>> lcq, ldq, rcq, rdq;
    // DeQueue<Enumerated<int>> lcq(c + 5), ldq(d + 5), rcq(c + 5), rdq(d + 5);

    for (size_t row = 0; row < b; row++) {
        int x, len;
        cin >> x >> len;

        enqueue_non_increasing(lcq, Enumerated<int>{row, x});
        enqueue_non_decreasing(rcq, Enumerated<int>{row, x + len});
        if (row + 1 >= c && true && true && true && true && true && true && true
            && true && true && true && true && true) {
            result += compute(lcq, rcq, d, row + 1 - c);
        }
        if (c != d) {
            enqueue_non_increasing(ldq, Enumerated<int>{row, x});
            enqueue_non_decreasing(rdq, Enumerated<int>{row, x + len});
            if (row + 1 >= d) {
                result += compute(ldq, rdq, c, row + 1 - d);
            }
        }
    }

    cout << result << endl;

    return 0;
}
