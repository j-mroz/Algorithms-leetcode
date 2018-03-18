//
// https://www.hackerrank.com/challenges/hacker-country/problem
//
#include <cmath>
#include <climits>
#include <limits>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;

static const long long INF = INT_MAX;

int N;
long long adjmatrix[500][500];

struct PathInfo {
    long long cost;
    int edges;
    double avg() {
        if (cost == INF)
            return INF/1;
        return (double)cost/edges;
    }
    bool lessThan(PathInfo& other) {
        if (cost*other.edges == other.cost*edges)
            return edges < other.edges;
        return avg() < other.avg();
    }
};

PathInfo mean[500];
long long dist[505][500];

long long gcd(long long a, long long b) {
    for (;;) {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}


int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int cost;
            cin >> cost;
            adjmatrix[i][j] = cost;

            if (i == j)
                adjmatrix[i][j] = INF;
        }
    }

    for (int i = 0; i < N; ++i)
        dist[0][i] = INF;
    dist[0][0] = 0;

    for (int i = 1; i <= N; ++i) {
        for (int u = 0; u < N; ++u) {
            dist[i][u] = INF;
            for (int v = 0; v < N; ++v) {
                dist[i][u] = min(dist[i][u], dist[i-1][v] + adjmatrix[v][u]);
            }
        }
    }


    PathInfo lambda = { INF, 1 };

    for (int u = 0; u < N; ++u) {
        mean[u] = { INT_MIN, 1 };
        for (int i = 0; i < N; ++i) {
            PathInfo path { dist[N][u] - dist[i][u], N - i };
            if (path.avg() > mean[u].avg()) {
                mean[u] = path;
            }
        }
        if (mean[u].avg() < lambda.avg()) {
            lambda = mean[u];
        }
    }

    int div = gcd(lambda.cost, lambda.edges);
    cout << lambda.cost/div << "/" << lambda.edges/div << endl;

    return 0;
}
