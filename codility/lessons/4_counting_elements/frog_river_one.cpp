// https://app.codility.com/programmers/lessons/4-counting_elements/frog_river_one/

#include <algorithm>
#include <limits>
#include <vector>
using namespace std;

static const int Infinity = numeric_limits<int>::max();

int solution(int fields_count, vector<int> &leaf_fall_timeline) {

    auto leaf_fall_time = vector<int>(fields_count, Infinity);

    for (int t = 0; (size_t)t < leaf_fall_timeline.size(); t++) {
        int leaf = leaf_fall_timeline[t] - 1;
        leaf_fall_time[leaf] = min(leaf_fall_time[leaf], t);
    }

    int last_fall_time = *max_element(leaf_fall_time.begin(),
                                      leaf_fall_time.end());
    if (last_fall_time != Infinity) {
        return last_fall_time;
    }
    return -1;
}
