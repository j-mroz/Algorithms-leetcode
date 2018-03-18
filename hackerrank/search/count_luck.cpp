//
// https://www.hackerrank.com/challenges/count-luck/problem
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <queue>
#include <unordered_set>
using namespace std;

using svec = vector<string>;
using ivec = vector<int>;

tuple<svec, int, int> read_forest() {
	int M, N;
	cin >> M >> N;
	auto forest = vector<string>(M);
	int x = -1, y = -1;
	for (int m = 0; m < M; ++m) {
		cin >> forest[m];
		for (int n = 0; n < N; ++n) {
			if (forest[m][n] == 'M') {
				x = m;
				y = n;
			}
		}
	}
	return make_tuple(forest, x, y);
}

int navigate_forest(const svec &forest, int x, int y) {
	auto M = forest.size();
	auto N = forest[0].size();

	auto steps_queue = queue<tuple<int, int, int>>();
	steps_queue.push(make_tuple(x, y, 0));
	auto visited = vector<ivec>(M, ivec(N, 0));
	visited[x][y] = 1;

	while (not steps_queue.empty()) {
		int x, y, magic;
		tie(x, y, magic) = steps_queue.front(), steps_queue.pop();

		int moves[4][2] = {
			{x-1, y}, {x+1, y}, {x, y-1}, {x, y+1},
		};

		auto move_count = 0;
		for (auto &move : moves) {
			if (move[0] >= 0 and move[0] < M and
				move[1] >= 0 and move[1] < N and
				visited[move[0]][move[1]] == 0 and
				(forest[move[0]][move[1]] == '.' or
				 forest[move[0]][move[1]] == '*')) {
				++move_count;
			}
		}
		for (auto &move : moves) {
			if (move[0] >= 0 and move[0] < M and
				move[1] >= 0 and move[1] < N and
				forest[move[0]][move[1]] == '*') {
				return (magic + (move_count > 1 ? 1 : 0));
			}
			if (move[0] >= 0 and move[0] < M and
				move[1] >= 0 and move[1] < N and
				visited[move[0]][move[1]] == 0 and
				forest[move[0]][move[1]] == '.') {
				steps_queue.push(
						make_tuple(move[0], move[1],
								   magic + (move_count > 1 ? 1 : 0)));
				visited[move[0]][move[1]] = 1;
			}
		}
	}
	return -1;
}

int main() {

	int tests = 0;
	cin >> tests;
	for (int t = 0; t < tests; ++t) {
		int x, y, k;
		svec forest;
		tie(forest, x, y) = read_forest();
		cin >> k;
		auto magic = navigate_forest(forest, x, y);
		if (magic == k) {
			cout << "Impressed" << endl;
		} else {
			cout << "Oops!" << endl;
		}
	}

    return 0;
}
