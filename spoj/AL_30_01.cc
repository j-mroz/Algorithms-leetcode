#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string anagram_pattern;
    size_t num_lines;
    cin >> anagram_pattern >> num_lines;

    vector<string> lines;
    copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(lines));
    lines.resize(num_lines);

    sort(anagram_pattern.begin(), anagram_pattern.end());
    auto result = count_if(lines.begin(), lines.end(), [&](auto &line) {
        sort(line.begin(), line.end());
        return line == anagram_pattern;
    });
    cout << result << endl;

    return 0;
}
