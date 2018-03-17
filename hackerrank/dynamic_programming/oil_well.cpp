//
// https://www.hackerrank.com/challenges/oil-well/problem
//

#include <cmath>
#include <climits>
#include <limits>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <cassert>
using namespace std;


struct point {
    int x;
    int y;
};

int grid[50][50];

vector<int> xpoints;
vector<int> ypoints;


struct rectangle {
    int left;
    int right;
    int top;
    int down;
};

int diameter(rectangle r) {
    return max(abs(r.left - r.right), abs(r.top - r.down));
}

int distance(point p, rectangle r) {
    return max(max(abs(p.x - r.right), abs(p.x - r.left)),
               max(abs(p.y - r.top),   abs(p.y - r.down)));
}

rectangle shrinkrectangle(rectangle rec) {
    while (!xpoints[rec.left] && rec.left < rec.right)
        rec.left++;
    while (!xpoints[rec.right] && rec.left < rec.right)
        rec.right--;
    while (!ypoints[rec.top] && rec.top < rec.down)
        rec.top++;
    while (!ypoints[rec.down] && rec.top < rec.down)
        rec.down--;
    return rec;
}
static int state[50][50][50][50];

int getCost(rectangle rec) {

    int cost = INT_MAX;
    if (rec.left >= rec.right && rec.top >= rec.down)
        return 0;

    assert(rec.left <= rec.right);
    assert(rec.top <= rec.down);

    rec = shrinkrectangle(rec);

    if (state[rec.left][rec.right][rec.top][rec.down])
        return state[rec.left][rec.right][rec.top][rec.down];

    int leftRight[] = {rec.left, rec.right};
    int topDown[] = {rec.top, rec.down};

    if (rec.left <= rec.right) {
        for (int lr : leftRight) {
            int lrCost = 0;

            for (int y = rec.top; y <= rec.down; ++y) {
                point p {lr, y};
                if (!grid[p.x][p.y])
                    continue;
                assert(p.x >= 0);
                assert(p.y >= 0);

                lrCost += diameter(rec);
                xpoints[p.x]--;
                ypoints[p.y]--;

            }
            cost = min(cost, lrCost + getCost(rec));
            for (int y = rec.top; y <= rec.down; ++y) {
                point p {lr, y};
                if (!grid[p.x][p.y])
                    continue;

                xpoints[p.x]++;
                ypoints[p.y]++;

            }
        }
    }
    if (rec.top <= rec.down) {
        for (int td : topDown) {
            int tdCost = 0;
            for (int x = rec.left; x <= rec.right; ++x) {
                point p {x, td};
                if (!grid[p.x][p.y])
                    continue;
                assert(p.x >= 0);
                assert(p.y >= 0);

                tdCost += diameter(rec);
                xpoints[p.x]--;
                ypoints[p.y]--;

            }
            cost = min(cost, tdCost + getCost(rec));
            for (int x = rec.left; x <= rec.right; ++x) {
                point p {x, td};
                if (!grid[p.x][p.y])
                    continue;

                xpoints[p.x]++;
                ypoints[p.y]++;

            }
        }
    }

    state[rec.left][rec.right][rec.top][rec.down] = cost;

    return cost;
}

int main() {

    int rowsCount, columnsCount;
    cin >> rowsCount >> columnsCount;
    xpoints.resize(rowsCount, 0);
    ypoints.resize(columnsCount, 0);
    for (int row = 0; row < rowsCount; ++row) {
        for (int column = 0; column < columnsCount; ++column) {
            int val;
            cin >> val;
            grid[row][column] = val;
            if (val != 0) {
                xpoints[row]++;
                ypoints[column]++;
            }
        }
    }

    unsigned long long result = 0;

    rectangle r { 0, rowsCount-1, 0, columnsCount-1 };

    while (!xpoints[r.left])
        r.left++;

    while (!xpoints[r.right])
        r.right--;

    while (!ypoints[r.top])
        r.top++;

    while (!ypoints[r.down])
        r.down--;

    result = getCost(r);

    cout << result << endl;


    return 0;
}
