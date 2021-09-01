

int solution(int N) {
    unsigned int n = static_cast<unsigned int>(N);
    int num_factors = 0;
    for (unsigned int d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            num_factors += 2;
        }
        if (d * d == n) {
            num_factors -= 1;
        }
    }
    return num_factors;
}

