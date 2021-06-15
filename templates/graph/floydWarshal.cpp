#include <iostream>
using namespace std;

static const int INF = 1 << 30;

struct Algo {
	void readInput() {
		cin >> N_;
		for (int i = 0; i < N_; ++i)
			for (int j = 0; j < N_; ++j)
				cin >> adjmatrix_[i][j];
	}

	void run() {
		findDc();
		floydWarshall();
		findCc();
	}

	void findDc() {
		// Find highest DC
		dc_ = 0;
		for (int i = 0; i < N_; ++i) {
			int dci = 0;
			for (int j = 0; j < N_; ++j)
				dci += adjmatrix_[i][j];
			if (dci > dc_)
				dc_ = dci;
		}
	}

	void findCc() {
		// Find lowest CC
		cc_ = 1<<30;
		for (int i = 0; i < N_; ++i) {
			int cci = 0;
			for (int j = 0; j < N_; ++j)
				cci += shortest_[i][j];
			if (cci < cc_)
				cc_ = cci;
		}
	}

	void floydWarshall() {
		for (int i = 0; i < N_; ++i) {
			for (int j = 0; j < N_; ++j) {
				if (adjmatrix_[i][j] != 0)
					shortest_[i][j] = adjmatrix_[i][j];
				else if (i == j)
					shortest_[i][j] = 0;
				else
					shortest_[i][j] = INF;
			}
		}

		for (int x = 0; x < N_; ++x) {
			for (int u = 0; u < N_; ++u) {
				for (int v = 0; v < N_; ++v) {
					if (shortest_[u][v] > shortest_[u][x] + shortest_[x][v]) {
						shortest_[u][v] = shortest_[u][x] + shortest_[x][v];
					}
				}
			}
		}
	}

	void printOutput() {
		cout << dc_ << " " << cc_ << endl;
	}

	int N_;
	int dc_;
	int cc_;
	int adjmatrix_[1000][1000];
	int shortest_[1000][1000];
} algo;

int main(int argc, char* argv[]) {
	int tests_count;
	cin >> tests_count;
	for (int i = 1; i <= tests_count; ++i) {
		algo.readInput();
		algo.run();
		cout << "#" << i << " ";
		algo.printOutput();
	}
	return 0;
}
