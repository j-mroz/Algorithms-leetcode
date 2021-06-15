#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

inline int round_power_of_2(int num) {
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num++;
    return num;
}

class SegmentTree {
    struct Node { int val; int min; };
    vector<Node> nodes_;
    int start_;
    int end_;
    int end_extended_;
    size_t leafs_base_;
    static constexpr int initial_min = numeric_limits<int>::max();

public:
    SegmentTree(int start, int end) {
        auto num_leafs = round_power_of_2(end - start);
        leafs_base_ = num_leafs;
        nodes_.resize(2 * num_leafs, Node{ 0, initial_min });
        start_ = start;
        end_ = end;
        end_extended_ = start_ + num_leafs;
    }

    void reset(int start, int end) {
        fill(nodes_.begin(), nodes_.end(), Node{ 0, initial_min });
        auto num_leafs = round_power_of_2(end - start);
        leafs_base_ = num_leafs;
        start_ = start;
        end_ = end;
        end_extended_ = start_ + num_leafs;
    }

    void set(int pos, int val) {
        auto x = leafs_base_ + pos - start_;
        nodes_[x] = { val, val };
        for (; x > 1; x = x/2) {
            nodes_[x/2].min = min(nodes_[x/2].min, nodes_[x].min);
        }
    }

    int query_min(int start, int end) {
        return query_min_impl(start, end, 1, start_, end_extended_);
    }

    int query_min_impl(int start, int end, int node, int node_start, int node_end) {
        assert(node < nodes_.size());
        // TODO: MAYBE BUG, maybe should be:
        // int result = odes_[node].val;
        int result = numeric_limits<int>::max();
        if (start <= node_start && node_end <= end) {
            result = nodes_[node].min;
        } else {
            auto mid = node_start + (node_end - node_start) / 2;
            if (start < mid) {
                result = min(result, query_min_impl(start, end, node * 2, node_start, mid));
            }
            if (mid < end) {
                result = min(result, query_min_impl(start, end, node * 2 + 1, mid, node_end));
            }
        }
        return result;
    }
};
