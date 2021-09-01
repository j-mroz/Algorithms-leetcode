#include <limits>
#include <vector>
using namespace std;

int solution(vector<int> &A) {
    size_t n = A.size();
    vector<int> prefix_sum(n);
    vector<int> suffix_sum(n);

    for (size_t i = 1; i < n - 1; i++) {
        prefix_sum[i] = max(prefix_sum[i - 1] + A[i], A[i]);
        prefix_sum[i] = max(prefix_sum[i], 0);
    }

    for (size_t i = n - 2; i > 0; i--) {
        suffix_sum[i] = max(suffix_sum[i + 1] + A[i], A[i]);
        suffix_sum[i] = max(suffix_sum[i], 0);
    }

    int best_double_slice = std::numeric_limits<int>::min();
    for (size_t i = 1; i < n - 1; i++) {
        best_double_slice = max(
            best_double_slice,
            prefix_sum[i - 1] + suffix_sum[i + 1]
        );
    }

    return best_double_slice;
}
