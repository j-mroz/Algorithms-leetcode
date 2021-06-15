#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;
using std::string;
using std::min;
using std::max;

vector<int> manacher(const string &text) {
    vector<int> rads(text.size());

    for (int i = 0, l = 0, r = -1; i < text.size(); i++) {
        int k = (i > r) ? 1 : min(rads[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < text.size() && text[i - k] == text[i + k]) {
            k++;
        }
        rads[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    return rads;
}

void palindrome_rads(string input, vector<int>& rads, bool odd) {
    rads.clear();
    rads.resize(input.length(), 0);

    int pivot = 1;
    int radius = 0;
    int k;

    while (pivot < input.length() ) {

        while (pivot+radius+odd <= input.length() && pivot-radius > 0 && input[pivot-radius-1] == input[pivot+radius+odd]) {
            radius++;
        }
        rads[pivot] = radius;
        k = 0;

        while ( ++k && rads[pivot-k] != radius-k && k < radius) {
            rads[pivot+k] = min(rads[pivot-k], radius-k);
        }
        radius = max(0, radius-k);
        pivot += k;
    }
}

void palindrom_odd(string input, vector<int>& p, bool is_even = false) {
    p.clear();
    p.resize(input.size(), 0);
    p[0] = 0;

    int step = 0;

    // Start from position 1 and increment the pivot after each itteration
    for (int pivot = 1; pivot < input.size(); ++pivot) {
        // Start with radius 0
        int radius = 0;

        if (step + p[step] > pivot)
            radius = std::min(p[step+step-pivot], p[step]+step-pivot);

        // Calculate radius for position input[pivot], span to two sides an check if identical
        if (!is_even)
            while (radius <= pivot && pivot+radius+1 < input.size() && input[pivot-radius-1] == input[pivot+radius+1])
                ++radius;
        else
            while (radius <= pivot && pivot+radius+1 < input.size() && input[pivot-radius] == input[pivot+radius-1])
                ++radius;


        // Optymized step incrementing
        if (radius + pivot > step + p[step])
            step = pivot;

        p[pivot] = max(radius, p[pivot]);
        if (is_even && pivot-1 >= 0)
            p[pivot-1] = max(radius, p[pivot-1]);

    }
}


int main() {
    vector<int> rads;
    palindrom_odd("abccba", rads, true);
    // palindrome_rads("aba", rads, true);
    for (vector<int>::iterator i = rads.begin(); i != rads.end(); ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;
    return 0;
}
