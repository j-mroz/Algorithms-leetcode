//
// https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


using ivec = vector<int>;
using imat = vector<ivec>;


imat read_matrix() {
	int m, n;
	cin >> m >> n;
	auto matrix = imat(m, ivec(n));
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> matrix[i][j];
		}
	}
	return matrix;
}

int visit(imat &matrix, int i, int j, int depth) {
	++depth;
	matrix[i][j] = -depth;

	auto moves = imat {
		{i-1, j-1},
		{i-1, j},
		{i-1, j + 1},
		{i, j - 1},
		{i, j + 1},
		{i+1, j-1},
		{i+1, j},
		{i+1, j + 1}
	};

	for (auto move : moves) {
		if (move[0] < 0 or move[0] >= matrix.size() or
			move[1] < 0 or move[1] >= matrix[0].size() or
			matrix[move[0]][move[1]] <= 0)
			continue;
		depth = visit(matrix, move[0], move[1], depth);
	}

	return depth;
}

int main() {
	auto matrix = read_matrix();
	int max_connected = 0;
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			if (matrix[i][j] <= 0)
				continue;
			auto connected = visit(matrix, i, j, 0);
			max_connected = max(max_connected, connected);

		}
	}
    cout << max_connected << endl;

    return 0;
}
