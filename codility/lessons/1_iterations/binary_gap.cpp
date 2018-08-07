// https://app.codility.com/programmers/lessons/1-iterations/

#include <bitset>
using namespace std;

int solution(int N) {
    static const size_t bit_count = 32;

    auto binary_sequence = bitset<bit_count>(N);

    size_t start_bit = 0;
    while (start_bit < bit_count && binary_sequence[start_bit] == 0) {
        start_bit++;
    }

    int current_gap = 0, longest_gap = 0;

    for (size_t bit = start_bit; bit < bit_count; bit++) {
        if (binary_sequence[bit]) {
            longest_gap = max(longest_gap, current_gap);
            current_gap = 0;
        } else {
            current_gap++;
        }
    }

    return longest_gap;
}
