#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    uint32_t src;
    uint32_t dst;
    uint32_t weight;
    bool cycle_heavy = false;
};

class DisjontSet {
    struct Node {
        size_t parent;
        size_t size;
    };
    vector<Node> nodes_;

public:
    DisjontSet(size_t size) : nodes_{size} {
        for (size_t i = 0; i < nodes_.size(); i++)
            nodes_[i]= { i, 1 };
    }

    inline size_t find_root(size_t x) {
        while (x != nodes_[x].parent) {
            auto next = nodes_[x].parent;
            nodes_[x].parent = nodes_[next].parent;
            x = next;
        }
        return x;
    }

    inline void connect(size_t x, size_t y) {
        x = find_root(x);
        y = find_root(y);
        if (x != y) {
            if (nodes_[x].size > nodes_[y].size)
                swap(x, y);
            nodes_[x].parent = y;
            nodes_[y].size += nodes_[x].size;
        }
    }

    inline bool connected(size_t x, size_t y) {
        return find_root(x) == find_root(y);
    }
};

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    auto nodes = DisjontSet{n + 1};
    auto edges = vector<Edge>{m};
    auto edges_by_weight = vector<Edge *>{m};

    for (size_t i = 0; i < m; i++) {
        cin >> edges[i].src >> edges[i].dst >> edges[i].weight;
        edges_by_weight[i] = &edges[i];
    }

    auto cmp_weight = [](auto a, auto b) { return a->weight < b->weight; };
    sort(edges_by_weight.begin(), edges_by_weight.end(), cmp_weight);

    auto group_start = edges_by_weight.begin();
    auto group_match = [&](auto e) { return (*group_start)->weight == e->weight; };

    while (group_start != edges_by_weight.end()) {
        auto group_end = find_if_not(group_start, edges_by_weight.end(), group_match);

        for (auto edge = group_start; edge != group_end; edge++)
            if (nodes.connected((*edge)->src, (*edge)->dst))
                (*edge)->cycle_heavy = true;
        for (auto edge = group_start; edge != group_end; edge++)
            nodes.connect((*edge)->src, (*edge)->dst);

        group_start = group_end;
    }

    for (auto &edge : edges)
        cout << (!edge.cycle_heavy ? "TAK" : "NIE") << endl;

    return 0;
}
