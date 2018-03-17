#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
using namespace std;


using enum_str = tuple<int, string>;

int main() {

    auto n = 0;
    cin >> n;

    auto str_chains = vector<vector<enum_str>>(n);

    for (auto i = 0; i < n; ++i) {
    	auto idx = 0;
    	string str;
    	cin >> idx;
    	cin >> str;
    	str_chains[idx].push_back(make_tuple(i, move(str)));
    }

    for (auto &chain : str_chains) {
    	for (auto &estr : chain) {
    		if (get<0>(estr) < n/2)
    			cout << "- ";
    		else
    			cout << get<1>(estr) << " ";
    	}
    }

    return 0;
}
