#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    auto n = 0ul;
    cin >> n;
    vector<int> arr(n);
    for (auto i = 0ul; i < n; ++i)
        cin >> arr[i];

    sort(begin(arr), end(arr));

    cout << arr[n/2] << endl;

    return 0;
}
