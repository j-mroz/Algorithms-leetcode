#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <tuple>
#include <vector>
using namespace std;

struct Segment {
    int start;
    int end;

    bool intersects(const Segment &other) const {
        return other.start < end && start < other.end;
    }
    bool covers(const Segment &other) const {
        return start <= other.start && other.end <= end;
    }
};

// class SegmentTree {
//     unique_ptr<SegmentTree> left_;
//     unique_ptr<SegmentTree> right_;
//     int load_ = 0;
//     int max_load_ = 0;
//     Segment segment_;

// public:
//     SegmentTree(int start, int end) {
//         segment_ = Segment{ start, end };
//     }

//     int max_load() const {
//         return max_load_;
//     }

//     void remove(const Segment &change_segment, int val) {
//         add(change_segment, -val);
//     }

//     void add(const Segment &change_segment, int val) {
//         if (segment_.intersects(change_segment)) {
//             if (change_segment.covers(segment_)) {
//                 load_ += val;
//             } else {
//                 expand();
//                 if (left_->segment_.intersects(change_segment) )
//                     left_->add(change_segment, val);
//                 if (right_->segment_.intersects(change_segment) )
//                     right_->add(change_segment, val);
//             }
//             max_load_ = load_;
//             if (right_ && left_)
//                 max_load_ += max(left_->max_load_, right_->max_load_);
//         }
//     }

// private:
//     void expand() {
//         if ((segment_.end - segment_.start) > 1 && !left_ && !right_) {
//             auto mid =  segment_.start + (segment_.end - segment_.start) / 2;
//             left_ = make_unique<SegmentTree>(segment_.start, mid);
//             right_ = make_unique<SegmentTree>(mid, segment_.end);
//         }
//     }
// };

inline int next_power_of_2(int num) {
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
    // 0 index is unused
    vector<int> load_;
    vector<int> max_load_;
    int start_;
    int end_;
    size_t leafs_base_;
    static const size_t root_index_ = 1;

public:
    SegmentTree(int start, int end) {
        auto num_leafs = next_power_of_2(end - start);
        leafs_base_ = num_leafs;
        load_.resize(2 * num_leafs, 0);
        max_load_.resize(2 * num_leafs, 0);
        start_ = start;
        end_ = end;
    }

    int max_load() const { return max_load_[root_index_]; }

    void remove(const Segment &change_segment, int val) {
        add(change_segment, -val);
    }

    // void add(const Segment &change_segment, int val) {
    //     auto l = leafs_base_ + change_segment.start - start_;
    //     auto r = l + (change_segment.end - change_segment.start - 1);

    //     while (l >= root_index_) {
    //         if (l < r - 1) {
    //             if (is_right_child(l)) {
    //                 load_[l] += val;
    //                 max_load_[l]  += val;
    //             }
    //             if (is_left_child(r)) {
    //                 load_[r] += val;
    //                 max_load_[r] += val;
    //             }
    //         }

    //         if (r < leafs_base_) {
    //             max_load_[l] = max(max_load_[left_child(l)],
    //             max_load_[right_child(l)]) + load_[l]; max_load_[r] =
    //             max(max_load_[left_child(r)], max_load_[right_child(r)]) +
    //             load_[r];
    //         }

    //         l = parrent(l);
    //         r = parrent(r);
    //     }
    // }

    void add(const Segment &change_segment, int val) {
        auto l = leafs_base_ + change_segment.start - start_;
        auto r = l + (change_segment.end - change_segment.start - 1);

        load_[l] += val;
        max_load_[l] += val;
        if (l != r) {
            load_[r] += val;
            max_load_[r] += val;
        }

        while (l >= root_index_) {
            if (l < r - 1) {
                if (is_left_child(l)) {
                    load_[right_sibling(l)] += val;
                    max_load_[right_sibling(l)] += val;
                }
                if (is_right_child(r)) {
                    load_[left_sibling(r)] += val;
                    max_load_[left_sibling(r)] += val;
                }
            }

            if (r < leafs_base_) {
                max_load_[l] =
                    max(max_load_[left_child(l)], max_load_[right_child(l)])
                    + load_[l];
                max_load_[r] =
                    max(max_load_[left_child(r)], max_load_[right_child(r)])
                    + load_[r];
            }

            l = parrent(l);
            r = parrent(r);
        }
    }

private:
    inline size_t left_child(size_t pos) { return 2 * pos; }
    inline size_t right_child(size_t pos) { return 2 * pos + 1; }
    inline bool is_left_child(size_t pos) { return pos % 2 == 0; }
    inline bool is_right_child(size_t pos) { return pos % 2 == 1; }
    inline size_t right_sibling(size_t pos) { return pos + 1; }
    inline size_t left_sibling(size_t pos) { return pos - 1; }
    inline size_t parrent(size_t pos) { return pos / 2; }
};

struct Rectangle {
    int x1, x2, y1, y2;
};

enum class SweepEventKind { START, END };

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);

    auto min_y = numeric_limits<int>::max(), max_y = numeric_limits<int>::min();

    vector<tuple<int, SweepEventKind, int>> x_axis;
    vector<Rectangle> rectangles;

    int num_rect;
    cin >> num_rect;

    for (int idx_rect = 0; idx_rect < num_rect; idx_rect++) {
        Rectangle rect;
        cin >> rect.x1 >> rect.y1 >> rect.x2 >> rect.y2;
        min_y = min(min_y, rect.y1);
        max_y = max(max_y, rect.y2);
        rectangles.push_back(rect);
        x_axis.emplace_back(rect.x1, SweepEventKind::START, idx_rect);
        x_axis.emplace_back(rect.x2, SweepEventKind::END, idx_rect);
    }

    sort(x_axis.begin(), x_axis.end());

    auto max_overlaps = 0;
    auto y_segments = SegmentTree{min_y, max_y + 1};
    for (auto [x, kind, idx_rect] : x_axis) {
        auto &rect = rectangles[idx_rect];
        if (kind == SweepEventKind::START) {
            y_segments.add(Segment{rect.y1, rect.y2 + 1}, 1);
            max_overlaps = max(max_overlaps, y_segments.max_load());
        } else {
            y_segments.remove(Segment{rect.y1, rect.y2 + 1}, 1);
        }
    }
    cout << max_overlaps << endl;

    return 0;
}
