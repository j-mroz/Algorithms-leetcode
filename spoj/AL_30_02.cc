#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (string line; getline(cin, line); ) {
        auto words_stream = istringstream(line);
        auto words = vector<string>();

        for (string word; words_stream >> word; ) {
            words.push_back(word);
        }

        auto prev_lead_character = words.back().at(0);
        for (auto &word : words) {
            swap(prev_lead_character, word[0]);
            reverse(word.begin() + 1, word.end());
        }

        copy(words.begin(), words.end(), ostream_iterator<string>(cout, " "));
        cout << "\n";
    }

    return 0;
}

