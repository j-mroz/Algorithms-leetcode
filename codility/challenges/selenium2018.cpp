//
// https://app.codility.com/programmers/challenges/
//
#include <vector>
#include <cstdlib>
using namespace std;

vector<int> counter(vector<int> &values, size_t max) {
    auto counter = vector<int>(max+1);
    for (auto v : values) {
        counter[v-1]++;
    }
    return counter;
}

int shifts_count(vector<int> &counter) {
    int acc = 0;
    int shifts = 0;
    for (int count : counter) {
        shifts += abs(acc);
        shifts %= 1000000007;
        acc += (count - 1);
        acc %= 1000000007;
    }
    return shifts;
}

int solution(vector<int> &X, vector<int> &Y) {
    auto xcounter = counter(X, X.size());
    auto ycounter = counter(Y, Y.size());
    return shifts_count(xcounter) + shifts_count(ycounter);
}
