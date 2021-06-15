#include <algorithm>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>
using namespace std;

static constexpr int NOT_MATCHED = -1;

class BipartiteMatcher {
    vector<vector<int>> left_adj_list;
    vector<int> left_match;
    vector<int> right_match;
    vector<bool> visited;

public:
    BipartiteMatcher(const vector<vector<int>> &left_adj_list, int num_right_nodes) {
        this->left_adj_list = left_adj_list;
        auto num_left_nodes = left_adj_list.size();
        left_match.resize(num_left_nodes, NOT_MATCHED);
        right_match.resize(num_right_nodes, NOT_MATCHED);
        visited.resize(num_left_nodes, false);
    }

    void solve() {
        auto prev_phase_succeed = true;
        while (prev_phase_succeed) {
            prev_phase_succeed = augment_matches();
        }
    }

    bool augment_matches() {
        fill(visited.begin(), visited.end(), false);
        bool augmented = false;
        for (auto node = 0; node < left_adj_list.size(); node++) {
            if (left_match[node] == NOT_MATCHED && augment_match(node)) {
                augmented = true;
            }
        }
        return augmented;
    }
    
    bool augment_match(int left_node) {
        if (!visited[left_node]) {
            visited[left_node] = true;
            for (auto right_node : left_adj_list[left_node]) {
                if (right_match[right_node] == NOT_MATCHED) {
                    match(left_node, right_node);
                    return true;
                }
            }
            for (auto right_node : left_adj_list[left_node]) {
                if (augment_match(right_match[right_node])) {
                    match(left_node, right_node);
                    return true;
                }
            }
        }
        return false;
    }

    inline void match(int left_node, int right_node) {
        right_match[right_node] = left_node;
        left_match[left_node] = right_node;
    }

    int num_matches() const {
        return count_if(left_match.cbegin(), left_match.cend(), [](auto x) {
            return x != NOT_MATCHED;
        });
    }
};

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);

    int num_left_nodes, num_right_nodes;
    cin >> num_left_nodes >> num_right_nodes;
    auto left_adj_list = vector<vector<int>>(num_left_nodes, vector<int>());
    
    for (auto node = 0; node < num_left_nodes; node++) {
        int num_node_edges;
        cin >> num_node_edges;
        left_adj_list[node].resize(num_node_edges);
        for (auto edge = 0; edge < num_node_edges; edge++) {
            cin >> left_adj_list[node][edge];
            left_adj_list[node][edge]--;
        }
    }

    auto matcher = BipartiteMatcher(move(left_adj_list), num_right_nodes);
    matcher.solve();
    cout << matcher.num_matches() << endl;

    return 0;
}
