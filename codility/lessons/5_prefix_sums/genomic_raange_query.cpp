#include <algorithm>
#include <string>
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

vector<int> solution(string &sequence, vector<int> &starts, vector<int> &ends) {
    vector<int> ret;
    vector<PreffixSumArray> sums;

    for (char letter : "ACGT") {
        vector<int> filtered;
        for (auto x : sequence) {
            filtered.push_back((x == letter));
        }
        sums.push_back(PreffixSumArray{filtered});
    }

    int num_queries = starts.size();
    for (int query = 0; query < num_queries; query++) {
        for (int impact = 1; impact <= 4; impact++) {
            if (sums[impact - 1].query(starts[query], ends[query] + 1) > 0) {
                ret.push_back(impact);
                break;
            }
        }
    }

    return ret;
}
