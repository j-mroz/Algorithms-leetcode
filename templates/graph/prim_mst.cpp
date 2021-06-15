#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define INF (1<<30)

struct Edge : public pair<int, int> {
	Edge(int weight, int dst) : pair(weight, dst) {}
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
		primMst(0);
	}

	void primMst(int start) {
		fill(prev_.begin(), prev_.end(), -1);
		fill(dist_.begin(), dist_.end(), INF);
		dist_[start] = 0;
		priority_queue<Edge> edge_queue;
		edge_queue.push(Edge(dist_[start], start));

		while (!edge_queue.empty()) {
			Edge e = edge_queue.top();
			edge_queue.pop();
			int u = e.dst();

			for (int i = 0; i < adjlist_[u].size(); ++i) {
				Edge uv = adjlist_[u][i];
				int v = uv.dst();

				// Find best distance from current tree
				if (dist_[v] > uv.weight()) {
					dist_[v] = uv.weight();
					prev_[v] = u;
					edge_queue.push(uv);
				}
			}
		}
	}

	void printOutput() {
		int sum = 0;
		for (int i = 0; i < dist_.size(); ++i) {
			sum += dist_[i];
		}
		cout << sum << endl;
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
