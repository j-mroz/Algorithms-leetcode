#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

struct EdgeDirected {
    uint32_t dst;
    uint32_t weight;
};

struct Vertex {
    vector<EdgeDirected> adjacent;
};

class Graph {
    vector<Vertex> vertices_;
    uint64_t total_weight_ = 0;

public:
    Graph(size_t num_vertex) : vertices_(num_vertex) {}

    void connect(uint32_t u, uint32_t v, uint32_t weight) {
        vertices_.at(u).adjacent.push_back(EdgeDirected{v, weight});
        vertices_.at(v).adjacent.push_back(EdgeDirected{u, weight});
        total_weight_ += weight;
    }

    uint64_t max_path() {
        auto visited = vector<bool>(vertices_.size());
        uint64_t max_path = 0;
        path_dfs(1, 0, max_path, visited);
        return  max_path;
    }

    uint64_t total_weight() {
        return total_weight_;
    }

private:
    uint64_t path_dfs(uint32_t src, uint64_t pre_path, uint64_t &max_path,
                      vector<bool> &visited) {
        uint64_t dfs_path = 0;
        if (!visited[src]) {
            visited[src] = true;
            for (auto &[dst, weight] : vertices_.at(src).adjacent) {
                if (!visited[dst]) {
                    auto succ_path = path_dfs(dst, pre_path + weight, max_path, visited);
                    max_path = max(max_path, pre_path + weight + succ_path);
                    dfs_path = max(dfs_path, succ_path + weight);
                    pre_path = max(pre_path, dfs_path);
                }
            }
        }
        return dfs_path;
    }
};

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    uint32_t n = 0;
    cin >> n;

    auto graph = Graph{n + 1};
    for (uint64_t e = 0; e < n - 1; e++) {
        uint32_t src, dst;
        cin >> src >> dst;
        graph.connect(src, dst, 1);
    }

    auto max_path = graph.max_path();
    // auto result = 2 * graph.total_weight() - max_path;
    // assert(2 * graph.total_weight() >= max_path);
    cout <<  max_path << "\n";

    return 0;
}
