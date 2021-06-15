// #include <cmath> 
#include <iostream>
using namespace std;

#define log2(X) ((unsigned) (8*sizeof(uint64_t) - __builtin_clzll((X)) - 1))

inline uint64_t bin_digits(uint64_t num) {
    // return num > 1 ? uint64_t(log2(num) + 1) : 1;
    return uint64_t(log2(num) + 1);
}

inline uint64_t concat_digits_len(uint64_t num) {
    uint64_t total = 0, len = 1;
    for (uint64_t size = 1; total + size <= num; size <<= 1) {
        len += size * bin_digits(total + 1);
        total += size;
    }
    len += bin_digits(total + 1) * (num - total);
    return len;
}


int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_tests;
    cin >> num_tests;

    for (int t = 0; t < num_tests; t++) {
        uint64_t num;
        cin >> num;
        cout << concat_digits_len(num) << "\n";
    }

    return 0;
}
