//
// https://www.hackerrank.com/challenges/common-child/problem
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

using ivec = vector<int>;
using imat = vector<ivec>;

int main() {
    string a, b;
    cin >> a >> b;

    auto matrix = imat( a.size(), ivec(b.size()) );

    for (int i = 0; i < a.size(); ++i) {
    	for (int j = 0; j < b.size(); ++j) {
    		matrix[i][j] = max(
    				i > 0 ? matrix[i-1][j] : 0,
    				j > 0 ? matrix[i][j-1] : 0);
    		if (a[i] == b[j]) {
    			matrix[i][j] = max(
    					i > 0 and j > 0 ? matrix[i-1][j-1] + 1 : 1,
    					matrix[i][j]);
    		}
    	}
    }

    cout << matrix[a.size()-1][b.size()-1] << endl;

    return 0;
}
