#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

static const int Inf =  1<<30;
static const int None =  -1;

struct Edge : public pair<int, int> {
	Edge(int weight, int dst) : pair(weight, dst) { }
	inline int dst() {
		return this->second;
	}
	inline int weight() {
		return this->first;
	}
};

struct Algo {
	void readInput() {
		int vertices, edges;
		cin >> vertices >> edges;
		adjlist_.resize(vertices);
		while (edges--) {
			int u, v, weight;
			cin >> u >> v >> weight;
			adjlist_[u].push_back(Edge(weight, v));
		}
		prev_.resize(vertices);
		dist_.resize(vertices);
	}

	void run() {
		belmanFordShort(0);
	}

	void belmanFordShort(int start) {
		fill(prev_.begin(), prev_.end(), None);
		fill(dist_.begin(), dist_.end(), Inf);
		dist_[start] = 0;

		int n = adjlist_.size();
		for (int i = 1; i <= n-1; ++i)
			relaxAll();
	}

	void relaxAll() {
		for (int u = 0; u < adjlist_.size(); ++u) {
			for (int vidx = 0; vidx < adjlist_[u].size(); ++vidx) {
				int v = adjlist_[u][vidx].dst();
				int uv_weiht = adjlist_[u][vidx].weight();
				relax(u, v, uv_weiht);
			}
		}
	}

	void relax(int u, int v, int uv_weight) {
		if (dist_[u] + uv_weight < dist_[v]) {
			dist_[v] = dist_[u] + uv_weight;
			prev_[v] = u;
		}
	}

	void printOutput() {
		for (int i = 0; i < dist_.size(); ++i) {
			cout << "0->" << i << ": " << dist_[i] << endl;
		}
	}

	vector<vector<Edge> > adjlist_;
	vector<int> prev_;
	vector<int> dist_;

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
