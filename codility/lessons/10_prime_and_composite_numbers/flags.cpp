#include <algorithm>
#include <vector>
using namespace std;

inline bool is_peak(vector<int> &A, size_t i) {
    return A[i - 1] < A[i] && A[i] > A[i + 1];
}

int solution(vector<int> &A) {
    size_t flags_begin = 0;
    size_t flags_end = A.size();

    while (flags_begin < flags_end) {
        size_t flags_taken = flags_begin + (flags_end - flags_begin)/2;
        size_t min_distance = flags_taken;
        size_t flags_used = 0;

        for (size_t i = 1; i < A.size() - 1 && flags_used < flags_taken; ) {
            if (is_peak(A, i)) {
                flags_used++;
                i += min_distance;
            } else {
                i++;
            }
        }
        if (flags_used < flags_taken) {
            flags_end = flags_taken;
        } else {
            flags_begin = flags_taken + 1;
        }

    }

    return flags_begin - 1;
}
