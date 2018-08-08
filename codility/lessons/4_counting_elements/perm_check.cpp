// https://app.codility.com/programmers/lessons/4-counting_elements/perm_check/

#include <unordered_set>
#include <vector>
using namespace std;

int solution(vector<int> &A) {
    auto values = unordered_set<int>(A.begin(), A.end());
    int min_allowed_value = 1,
        max_allowed_value = (int)A.size();
    for (auto value : values) {
        if (value < min_allowed_value || value > max_allowed_value) {
            return 0;
        }
    }
    return (int)(values.size() == A.size());
}
