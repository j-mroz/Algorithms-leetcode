#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NONE (-1)

typedef pair<int, int> vertex_pair_t;

struct Edge : public pair<int, vertex_pair_t> {
	Edge(int weight, int src, int dst) : pair<int, vertex_pair_t>(weight, vertex_pair_t(src, dst)) {}
	inline int src() {
		return this->second.first;
	}
	inline int dst() {
		return this->second.second;
	}
	inline int weight() {
		return this->first;
	}
};

struct Algo {
	void readInput() {
		int vertices, edges;
		cin >> vertices >> edges;
		edges_.reserve(edges);
		while (edges--) {
			int u, v, weight;
			cin >> u >> v >> weight;
			edges_.push_back(Edge(weight, u, v));
		}
		sets_.resize(vertices);
		mst_adjlist_.resize(vertices);
	}

	void run() {
		kruskalMst(0);
	}

	void kruskalMst(int start) {
		fill(sets_.begin(), sets_.end(), NONE); //Bug? not NONE?
		sort(edges_.begin(), edges_.end());

		for (int i = 0; i < edges_.size(); ++i) {
			int u = edges_[i].src();
			int v = edges_[i].dst();
			if (findSet(u) != findSet(v)) {
				addMstEdge(edges_[i]);
				makeUnion(u, v);
			}
		}
	}

	void addMstEdge(Edge& e) {
		mst_adjlist_[e.src()].push_back(e);
	}

	int findSet(int u) {
		if (sets_[u] == NONE)
			return u;
		sets_[u] = findSet(sets_[u]);
		return sets_[u];
	}

	void makeUnion(int u, int v) {
		int xset = findSet(u);
		int vset = findSet(v);
		if (xset != vset)
			sets_[xset] = vset;
	}

	void printOutput() {
		int sum = 0;
		for (int i = 0; i < mst_adjlist_.size(); ++i)
			for (int j = 0; j < mst_adjlist_[i].size(); ++j)
				sum += mst_adjlist_[i][j].weight();
		cout << sum << endl;
	}

	vector<vector<Edge> > mst_adjlist_;
	vector<int> sets_;
	vector<Edge> edges_;
};

int main(int argc, char* argv[]) {
	int tests_count;
	cin >> tests_count;
	while (tests_count--) {
		Algo algo;
		algo.readInput();
		algo.run();
		algo.printOutput();
	}
	return 0;
}
