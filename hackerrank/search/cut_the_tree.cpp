//
// https://www.hackerrank.com/challenges/cut-the-tree/problem
//

#include <tuple>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;



struct link {
    int dst;
};

struct TreeInfo {
    const vector<int> &nodeWeights;
    const vector<vector<link>> &links;
    vector<char> &visited;
    long long sum;
};

tuple<unsigned int, unsigned int>
cutTheTree(TreeInfo &tree, int node, unsigned int currBestDiff) {

    auto bestDiff = currBestDiff;
    auto weight = tree.nodeWeights[node];

    tree.visited[node] = 1;

    for (auto &link : tree.links[node]) {
        if (tree.visited[link.dst] != 0)
            continue;

        auto subTreeBestDiff = 0ll;
        auto subTreeWeight = 0ll;
        tie(subTreeBestDiff, subTreeWeight) =
            cutTheTree(tree, link.dst, bestDiff);

        if (subTreeBestDiff < bestDiff) {
            bestDiff = subTreeBestDiff;
        }

        if (abs(tree.sum - 2*subTreeWeight) < bestDiff) {
            bestDiff = abs(tree.sum - 2*subTreeWeight);
        }

        weight += subTreeWeight;
    }

    return make_tuple(bestDiff, weight);
}

int main() {
    auto N = 0;
    cin >> N;
    vector<int> nodeWeights(N);
    vector<vector<link>> links(N);
    unsigned int linksSum = 0;

    for (int i = 0; i < N; ++i) {
        cin >> nodeWeights[i];
        linksSum += nodeWeights[i];
    }

    for (int i = 0; i < N-1; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        links[u].push_back({v});
        links[v].push_back({u});
    }
    vector<char> visited(N, 0);
    auto tree = TreeInfo { nodeWeights, links, visited, linksSum };
    auto result = 0ul;
    tie(result, std::ignore) = cutTheTree(tree, 0, linksSum);

    cout << result << endl;

    return 0;
}
