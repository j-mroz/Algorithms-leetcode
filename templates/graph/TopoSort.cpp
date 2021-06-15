#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Algo {
	void readInput() {
		int vertices, edges;
		cin >> vertices >> edges;
		adjlist_.resize(vertices);
		while (edges--) {
			int u, v;
			cin >> u >> v;
			adjlist_[u].push_back(v);
		}
	}

	void run() {
		topoSort();
	}

	void topoSort() {
		vector<bool> visited(adjlist_.size(), false);
		vector<int> finish(adjlist_.size(), -1);
		vector<int> sorted;
		sorted.reserve(adjlist_.size());

		finish_timer_ = 0;
		for (int u = 0; u < adjlist_.size(); ++u) {
			if (!visited[u])
				topoDfs(u, visited, finish, sorted);
		}
		reverse(sorted.begin(), sorted.end());
		have_cycle_ = haveCycle(finish);
	}

	void topoDfs(int u, vector<bool>& visited, vector<int>& finish, vector<int>& sorted) {
		visited[u] = true;
		for (int i = 0; i < adjlist_.size(); ++i) {
			int v = adjlist_[u][i];
			if (!visited[v])
				topoDfs(v, visited, finish, sorted);
		}
		finish[u] = ++finish_timer_;
		sorted.push_back(u);
	}

	bool haveCycle(vector<int>& finish) {
		for (int u = 0; u < adjlist_.size(); ++u) {
			for (int i = 0; adjlist_.size(); ++i) {
				int v = adjlist_[u][i];
	            if (finish[v] <= finish[u]) {
	            	return true;
	            }
			}
		}
		return false;
	}

	void printOutput() {
		cout << have_cycle_ << endl;
	}

	bool have_cycle_;
	vector<vector<int> > adjlist_;
	int finish_timer_;
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
