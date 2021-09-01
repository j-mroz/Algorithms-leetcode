#include <vector>
using namespace std;

class PreffixSumArray {
     vector<int> sums;

public:
    PreffixSumArray(vector<int> &arr) {
        sums.resize(arr.size() + 1, 0);
        for (size_t i = 0; i < arr.size(); i++) {
            sums[i + 1] = sums[i] + arr[i];
        }
    }

    int query(size_t start, size_t end) {
        return sums[end] - sums[start];
    }
};

int solution(vector<int> &arr) {
    PreffixSumArray prefix_sums{arr};

    int passing_cars = 0;
    int end = arr.size();

    for (int pos = 0; pos < end; pos++) {
        if (arr[pos] == 0) {
            passing_cars += prefix_sums.query(pos + 1, end);
            if (passing_cars > 1000000000 || passing_cars < 0) {
                return -1;
            }
        }
    }

    return passing_cars;
}

