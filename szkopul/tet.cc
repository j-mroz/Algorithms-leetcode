#include <iostream>
#include <memory>
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

class SegmentTree {
    unique_ptr<SegmentTree> left_;
    unique_ptr<SegmentTree> right_;
    int max_load_ = 0;
    int max_sub_load_ = 0;
    Segment segment_;

public:
    SegmentTree(int start, int end, int val = 0) {
        segment_ = Segment{start, end};
        max_load_ = max_sub_load_ = 0;
    }

    void update_max(const Segment &update_segment, int val) {
        if (update_segment.covers(segment_)) {
            max_load_ = max(max_load_, val);
            max_sub_load_ = max(max_sub_load_, val);
        } else if (update_segment.intersects(segment_)) {
            expand();
            if (update_segment.intersects(left_->segment_))
                left_->update_max(update_segment, val);
            if (update_segment.intersects(right_->segment_))
                right_->update_max(update_segment, val);
            max_sub_load_ = max(left_->max_sub_load_, right_->max_sub_load_);
        }
    }

    int query_max(const Segment &query_segment) {
        int result = max_load_;
        if (query_segment.covers(segment_) || (!left_ && !right_)) {
            result = max_sub_load_;
        } else {
            if (query_segment.intersects(left_->segment_))
                result = max(result, left_->query_max(query_segment));
            if (query_segment.intersects(right_->segment_))
                result = max(result, right_->query_max(query_segment));
        }
        return result;
    }

private:
    void expand() {
        if ((segment_.end - segment_.start) > 1 && !left_ && !right_) {
            auto mid = segment_.start + (segment_.end - segment_.start) / 2;
            left_ = make_unique<SegmentTree>(segment_.start, mid, max_load_);
            right_ = make_unique<SegmentTree>(mid, segment_.end, max_load_);
        }
    }
};

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);

    int width, num_segments;
    cin >> width >> num_segments;
    auto segment_tree = SegmentTree{0, width + 1};

    for (int i = 0; i < num_segments; i++) {
        int len, x;
        cin >> len >> x;
        auto segment = Segment{x, x + len};
        auto max = segment_tree.query_max(segment);
        segment_tree.update_max(segment, max + 1);
    }

    cout << segment_tree.query_max(Segment{0, width + 1}) << endl;

    return 0;
}
