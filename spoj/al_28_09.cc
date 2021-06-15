#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

static array<array<char, 501>, 501> text;
static array<array<int, 501>, 501> pal_row;
static array<array<int, 501>, 501> pal_col;
static vector<int> min_widths{501};

void manacher_row(size_t row, size_t size) {
    for (int i = 0, l = 0, r = -1; i < size; i++) {
        int k = (i > r) ? 1 : min(pal_row[row][l + r - i], r - i + 1);
        while (0 <= i - k && i + k < size && text[row][i - k] == text[row][i + k]) {
            k++;
        }
        pal_row[row][i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
}

void manacher_col(size_t col, size_t size) {
    for (int i = 0, l = 0, r = -1; i < size; i++) {
        int k = (i > r) ? 1 : min(pal_col[l + r - i][col], r - i + 1);
        while (0 <= i - k && i + k < size && text[i - k][col] == text[i + k][col]) {
            k++;
        }
        pal_col[i][col] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
}

int64_t solve(int size) {
    for (int i = 0; i < size; i++) {
        manacher_row(i, size);
        manacher_col(i, size);
    }

    int64_t result = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            min_widths.clear();

            min_widths.push_back(pal_row[i][j]);
            for (int k = 1; k < pal_col[i][j]; k++) {
                int w = min(min_widths.back(), min(pal_row[i - k][j], pal_row[i + k][j]));
                min_widths.push_back(w);
            }

            int height = pal_col[i][j];
            for (int width = 1; width <= pal_row[i][j]; width++) {
                int l  = j - width + 1, r = j + width - 1;
                while (pal_col[i][l] < height || pal_col[i][r] < height ||
                       min_widths[height - 1] < width) {
                    height--;
                }
                // inv: height <= ALL column palindroms in range [j-width+1, j+width-1]
                // inv: width  <= ALL row palindroms in range [i-heigh, i+height]
                result += height;
            }
        }
    }

    return result;
}

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t tests;
    cin >> tests;

    for (size_t t = 0; t < tests; t++) {
        int size;
        cin >> size;

        for (int i = 0; i < size; i++) {
            cin >> text[i].data();
        }

        cout << solve(size) << endl;
    }

    return 0;
}
