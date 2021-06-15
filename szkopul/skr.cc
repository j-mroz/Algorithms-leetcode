#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

constexpr inline uint64_t round_pow2(uint64_t x) {
    return uint64_t{1} << (sizeof(uint64_t) * 8 - __builtin_clzll(x - 1));
}

// struct Range {
//     int lo;
//     int end;

//     inline bool intersects(const Range &other) const {
//         return other.lo < end && lo < other.end;
//     }
//     inline bool contains(const Range &other) const {
//         return lo <= other.lo && other.end <= end;
//     }
// };

// struct RangeSplit {
//     Range left;
//     Range right;
// };


// class SegmentTree {
//     struct Node {
//         int val;
//         int max;
//     };
//     vector<Node> nodes_;
//     Range tree_range_;

// public:
//     SegmentTree(int lo, int end) {
//         const size_t count = round_pow2(end - lo);
//         nodes_.resize(2 * count, Node{0, numeric_limits<int>::min()});
//         tree_range_ = Range{lo, lo + (int)count};
//     }

//     inline void set(int lo, int end, int val) {
//         set(Range{lo, end}, tree_range_, 1, val);
//     }

//     inline int query_max(int lo, int end) const {
//         return query_max(Range{lo, end}, tree_range_, 1);
//     }

// private:
//     void set(const Range &change, const Range &node, int index, int val) {
//         if (change.contains(node)) {
//             nodes_[index].val = val;
//             nodes_[index].max = max(nodes_[index].max, val);
//             return;
//         }

//         const auto [left, right] = split_range(node);
//         if (change.intersects(left))
//             set(change, left, 2 * index, val);
//         if (change.intersects(right))
//             set(change, right, 2 * index + 1, val);
//         nodes_[index].max = max(nodes_[index].max, (nodes_[2 * index].max));
//         nodes_[index].max = max(nodes_[index].max, (nodes_[2 * index + 1].max));
//     }

//     int query_max(const Range &query, const Range &node, int index) const {
//         if (query.contains(node)) {
//             return nodes_[index].max;
//         }

//         const auto [left, right] = split_range(node);
//         int max_val = nodes_[index].val;
//         if (query.intersects(left))
//             max_val = max(max_val, query_max(query, left, 2 * index));
//         if (query.intersects(right))
//             max_val = max(max_val, query_max(query, right, 2 * index + 1));
//         return max_val;
//     }

//     RangeSplit split_range(const Range &parent) const {
//         const auto mid = parent.lo + (parent.end - parent.lo) / 2;
//         return {Range{parent.lo, mid}, Range{mid, parent.end}};
//     }
// };

class SegmentTree {
    struct Node { int val; int max; };
    vector<Node> nodes_;
    int lo_;
    int hi_;

public:
    SegmentTree(int lo, int end) {
        const size_t count = round_pow2(end - lo);
        nodes_.resize(2 * count, Node{ 0, numeric_limits<int>::min() });
        lo_ = lo;
        hi_ = lo_ + count;
    }

    inline void set(int lo, int end, int val) {
        set(lo, end, 1, lo_, hi_, val);
    }

    inline int query_max(int lo, int end) const {
        return query_max(lo, end, 1, lo_, hi_);
    }

private:
    void set(int lo, int hi, int node, int node_lo, int node_hi, int val) {
        const auto node_mid = node_lo + (node_hi - node_lo) / 2;

        if (lo <= node_lo && node_hi <= hi) {
            nodes_[node].val = val;
            nodes_[node].max = max(nodes_[node].max, val);
            return;
        }

        if (lo < node_mid) {
            set(lo, hi, 2*node, node_lo, node_mid, val);
            nodes_[node].max = max(nodes_[node].max, nodes_[2*node].max);
        }
        if (node_mid < hi) {
            set(lo, hi, 2*node + 1, node_mid, node_hi, val);
            nodes_[node].max = max(nodes_[node].max, nodes_[2*node + 1].max);
        }
    }

    int query_max(int lo, int hi, int node, int node_lo, int node_hi) const {
        const auto node_mid = node_lo + (node_hi - node_lo) / 2;

        if (lo <= node_lo && node_hi <= hi) {
            return nodes_[node].max;
        }

        int result = nodes_[node].val;
        if (lo < node_mid)
            result = max(result, query_max(lo, hi, 2*node, node_lo, node_mid));
        if (node_mid < hi)
            result = max(result, query_max(lo, hi, 2*node + 1, node_mid, node_hi));
        return result;
    }
};

bool move_exist(const vector<int> &watched, const SegmentTree &reachable) {
    for (size_t i = 1; i < watched.size(); ++i) {
        const auto a = watched[i - 1] + 1;
        const auto b = watched[i];
        if (a < b && (reachable.query_max(a, b) > 0)) {
            return true;
        }
    }
    return false;
}

void connect_reachable(const vector<int> &watched, SegmentTree &reachable) {
    for (size_t i = 1; i < watched.size(); ++i) {
        const auto a = watched[i - 1] + 1;
        const auto b = watched[i];
        if (a < b) {
            reachable.set(a, b, 1);
        }
    }
}

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    SegmentTree reachable{1, (int)n + 1};
    reachable.set(1, 2, 1);

    vector<int> watched;
    watched.reserve(2 * n);

    size_t iter;
    for (iter = 0; iter < m; iter++) {
        size_t num_watched;
        cin >> num_watched;

        watched.resize(num_watched + 2);
        watched[0] = 0; // lo guardian
        for (size_t i = 1; i <= num_watched; i++) {
            cin >> watched[i];
        }
        watched[num_watched + 1] = (int)n + 1; // end guardian

        if (move_exist(watched, reachable)) {
            connect_reachable(watched, reachable);
        }

        if (reachable.query_max(n, n + 1) > 0 && watched[num_watched] != n) {
            break;
        }
    }

    cout << iter << endl;

    return 0;
}
