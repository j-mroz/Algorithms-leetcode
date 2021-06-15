//
// https://app.codility.com/programmers/challenges/germanium2018/
//

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;


struct nest {
    int level;
    int order;
    // int left_paths_acc;
    // int right_paths_acc;
    int in_left;
    int in_right;
    int out_left;
    int out_right;
};

void sort_by_level(auto begin, auto end) {
    sort(begin, end, [](auto &a, auto &b) { return a.level < b.level; });
}

vector<nest> make_nests(vector<int> &H) {
    vector<nest> nests(H.size());
    for (int i = 0; (size_t)i < H.size(); ++i) {
        nests[i].level = H[i];
        nests[i].order = i;
    }
    return nests;
}

int left_to_right(auto &prev, auto &current) {
    return prev.order < current.order;
}

class query_tree {
public:
    query_tree(int size) {
        nodes.resize(size + 1);
    }

    int query_sum(int first, int last) {
        validate_range(first);
        validate_range(last);
        return query_sum(last) -  query_sum(first-1);
    }

    int query_sum(int last) {
        int result = 0;
        for (int i = last + 1; i > 0; i -= lsb(i)) {
            result += nodes[i];
        }
        return result;
    }

    void update(int index, int value) {
        for (int i = index + 1; i < nodes.size(); i += lsb(i)) {
            nodes[i] += value;
        }
    }
private:
    int lsb(int num) { return num & (-num); }

    void validate_range(int index) {
        if  (index+1 >= nodes.size()) {
            string msg = "query tree index " + to_string(index) + " error";
            throw std::out_of_range(msg);
        }
    }

private:
    vector<int> nodes;
};


int solution(vector<int> &H) {
    auto nests_count = H.size();
    auto nests = make_nests(H);
    sort_by_level(nests.begin(), nests.end());

    query_tree nests_set(nests_count);
    for (auto &nest : nests) {
        nests_set.update(nest.order, 1);
    }

    for (auto &nest : nests) {
        nests_set.update(nest.order, -1);
        nest.out_left = nests_set.query_sum(0, nest.order);
        nest.out_right = nests_set.query_sum(nest.order, nests_count-1);
    }

    query_tree nests_set2(nests_count);
    for (auto &nest : nests) {
        nests_set.update(nest.order, 1);
    }
    for (int i = nests.size(); i >= 0; i++) {
        auto &nest = nests[i];
        nests_set.update(nest.order, -1);
        nest.out_left = nests_set2.query_sum(0, nest.order);
        nest.out_right = nests_set2.query_sum(nest.order, nests_count-1);
    }

    int result;
    for (auto &nest : nests) {
        result += nest.in_left + nest.in_right;
        result += nest.out_left + nest.out_right;
    }

    return 0;
}



// void dump(auto &out) {
//     for (int i = 0; i < nodes.size(); i++) {
//         out << "{ index:" << i
//             << " value:" << nodes[i] << "} " << endl;
//     }
// }


// int solution(vector<int> &H) {
//     auto nests_count = H.size();
//     auto nests = make_nests(H);
//     sort_by_level(nests.begin(), nests.end());
//
//     query_tree nests_set(nests_count);
//     for (auto &nest : nests) {
//         nests_set.update(nest.order, 1);
//     }
//
//     int visited = 0;
//     int in_paths = 0;
//
//     for (auto &nest : nests) {
//         in_paths += visited;
//         nests_set.update(nest.order, -1);
//
//         int left_levels_count = nests_set.query_sum(0, nest.order);
//         int right_levels_count = nests_set.query_sum(nest.order, nests_count-1);
//
//         cout << "{ order:" << nest.order
//              << " level:" << nest.level
//              << " left_levels:" << left_levels_count
//              << " right_levels:" << right_levels_count
//              << " visited:" << visited
//              << " in_paths:" << in_paths
//              << " }" << endl;
//         visited++;
//
//         // adds a virtual destination nest
//         bool is_top_nest = (left_levels_count + right_levels_count) == 0;
//         if (is_top_nest) {
//             right_levels_count = 1;
//         }
//
//         nest.left_paths_acc = (in_paths +1) * left_levels_count;
//         nest.right_paths_acc = (in_paths +1) * right_levels_count;
//
//         cout << "{ level:" << nest.level << " left:" << nest.left_paths_acc
//              << " right:" << nest.right_paths_acc << " }" << endl;
//
//     }
//
//     return nests[nests.size() - 2].left_paths_acc +
//            nests[nests.size() - 2].right_paths_acc;
// }
