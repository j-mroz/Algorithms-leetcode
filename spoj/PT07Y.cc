#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct EdgeDirected {
    uint32_t dst;
    uint32_t weight;
    uint32_t id;
};


struct Vertex {
    vector<EdgeDirected> adjacent;
};

class Graph {
    vector<Vertex> vertices_;

public:
    Graph(size_t num_vertex) : vertices_(num_vertex) {}

    void connect(uint32_t u, uint32_t v, uint32_t weight, uint32_t id) {
        vertices_.at(u).adjacent.push_back(EdgeDirected{v, weight, id});
        vertices_.at(v).adjacent.push_back(EdgeDirected{u, weight, id});
    }

    vector<uint32_t> find_cycle() {
        auto cycle = vector<uint32_t>();
        auto visited = vector<bool>(vertices_.size());
        auto traversed = unordered_set<uint32_t>();
        for (uint32_t u = 1; u < vertices_.size(); u++) {
            if (visited[u])
                continue;
            cycle.clear();
            if (find_cycle_dfs(1, visited, traversed, cycle)) {
                return cycle;
            }
        }
        return {};
    }

private:
    bool find_cycle_dfs(uint32_t src, vector<bool> &visited,
                        unordered_set<uint32_t> &traversed, vector<uint32_t> &path) {
        path.push_back(src);
        visited[src] = true;
        for (auto &edge : vertices_.at(src).adjacent) {
            if (traversed.count(edge.id) > 0)
                continue;
            traversed.insert(edge.id);
            if (visited[edge.dst]) {
                auto cycle_start = find(begin(path), end(path), edge.dst);
                assert(cycle_start != end(path));
                path.erase(begin(path), cycle_start);
                return true;
            }
            if (find_cycle_dfs(edge.dst, visited, traversed, path)) {
                return true;
            }
        }
        path.pop_back();
        return false;
    }
};

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    uint32_t n = 0, m = 0;
    cin >> n >> m;

    auto graph = Graph{n + 1};
    for (uint32_t e = 0; e < m; e++) {
        uint32_t u, v;
        cin >> u >> v;
        graph.connect(u, v, 0, e+1);
    }
    auto cycle = graph.find_cycle();

    if (m == n - 1 && cycle.empty()) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
