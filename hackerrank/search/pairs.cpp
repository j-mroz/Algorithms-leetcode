//
// https://www.hackerrank.com/challenges/pairs/problem
//
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include <iterator>

int pairs(vector<int> numbers, int diff) {
    int ans = 0;

    sort(begin(numbers), end(numbers));

    for (auto val : numbers) {
        auto b = lower_bound(begin(numbers), end(numbers),  val + diff);
        auto e = upper_bound(begin(numbers), end(numbers),  val + diff);
        if (b == numbers.end() or *b != (val + diff))
            continue;
        ans += (e - b);
    }

    return ans;
}


/* Tail starts here */
int main() {
    int res;

    int _a_size,_k;
    cin >> _a_size>>_k;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    vector<int> _a;
    int _a_item;
    for(int _a_i=0; _a_i<_a_size; _a_i++) {
        cin >> _a_item;
        _a.push_back(_a_item);
    }

    res = pairs(_a,_k);
    cout << res;

    return 0;
}
