//
// https://www.hackerrank.com/challenges/gem-stones/submissions/code/17863284
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>
#include <iterator>
using namespace std;

using ivec = vector<int>;

void count_elements(const string &rock, ivec& counter) {
	for (char elemnent : rock) {
		if (elemnent >= 'A' and elemnent <= 'Z') {
			assert(0 && "unreachable");
		} else if (elemnent >= 'a' and elemnent <= 'z') {
			++counter[elemnent - 'a'];
		}
	}
}


int main() {
   	int n;
   	cin >> n;

   	static const int alphabet_size = 'z' - 'a' + 1;
   	auto gem_elements = ivec(alphabet_size);
   	auto rock_elements = ivec(alphabet_size);

   	for (int i = 0; i < n; ++i) {

   		string rock;
   		cin >> rock;
   		fill(rock_elements.begin(), rock_elements.end(), 0);
   		count_elements(rock, rock_elements);

   		for (int e = 0; e < rock_elements.size(); ++e) {
   			if (rock_elements[e] > 0) {
   				++gem_elements[e];
   			}
   		}
   	}

   	auto answer = count_if(gem_elements.begin(), gem_elements.end(), [n](int v) {
   		return v == n;
   	});

   	cout << answer << endl;
}
