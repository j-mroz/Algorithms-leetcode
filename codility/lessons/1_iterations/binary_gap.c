// https://app.codility.com/programmers/lessons/1-iterations/

// ntz - see hacker delight
int ntz(unsigned x) {
    const char u = 0; //unuesed
    static char table[37] = {
        32, 0,  1, 26,  2, 23, 27,
        u,  3, 16, 24, 30, 28, 11,  u, 13,  4,
        7, 17,  u, 25, 22, 31, 15, 29, 10, 12,
        6,  u, 21, 14,  9,  5, 20,  8, 19, 18
    };
    x = (x & -x) % 37;
    return table[x];
}

int solution(int N) {
    int longest_gap = 0;

    N >>= ntz(N);
    while (N > 0) {
        int trailing_zeros = ntz(N);
        longest_gap = (trailing_zeros > longest_gap) ? trailing_zeros : longest_gap;
        N >>= (trailing_zeros + 1);
    }

    return longest_gap;
}
