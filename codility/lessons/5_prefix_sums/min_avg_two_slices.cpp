#include <limits>
#include <vector>
using namespace std;

class PreffixSumArray {
     vector<int> sums;

public:
    PreffixSumArray(vector<int> &arr) : sums(arr.size() + 1, 0) {
        for (size_t i = 0; i < arr.size(); i++) {
            sums[i + 1] = sums[i] + arr[i];
        }
    }

    int query(size_t start, size_t end) {
        return sums[end] - sums[start];
    }
};

int solution(vector<int> &numbers) {
    PreffixSumArray sums{numbers};
    double best_avg = numeric_limits<double>::max();
    size_t best_start = 0;

    for (size_t start = 0; start < numbers.size() - 1; start++) {
        for (int len = 2; len <= 3 && start + len <= numbers.size(); len++) {
            int sum = sums.query(start, start + len);
            double avg = static_cast<double>(sum) / len;
            if (avg < best_avg) {
                best_avg = avg;
                best_start = start;
            }
        }
    }

    return best_start;
}
