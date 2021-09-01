#include <algorithm>
#include <cstdint>

int solution(int N) {
    uint32_t n = static_cast<uint32_t>(N);
    uint32_t min_perimeter = 2 * (n + 1);

    for (uint32_t a = 1; a * a <= n; a++) {
        if (n % a == 0) {
            uint32_t b = n / a;
            min_perimeter = min(min_perimeter, 2 * (a + b));
        }
    }

    return static_cast<int>(min_perimeter);
}
