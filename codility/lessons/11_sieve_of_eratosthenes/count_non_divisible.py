# https://app.codility.com/programmers/lessons/11-sieve_of_eratosthenes/count_non_divisible/

from collections import defaultdict
from bisect import bisect_right, bisect_left

def solution(A):
    values_count = len(A)
    values_indexed = sorted((v, i) for (i, v) in enumerate(A))
    values, indexes = zip(*values_indexed)
    max_value = max(values)

    divisors_counter = defaultdict(int)

    # This is O(n log n) because those two loop are doing
    # n + n/2 + n/3 + ... n/n iterations at most, so it's harmonic series.
    i = 0
    while i < values_count:
        value = values[i]
        range_start = bisect_left(values, value)
        range_end = bisect_right(values, value)
        range_count = range_end - range_start
        for j in range(value, max_value+1, value):
            divisors_counter[j] += range_count
        i += range_count

    result = [0] * values_count
    for i, value in enumerate(values):
        result[indexes[i]] += values_count - divisors_counter[value]

    return result;
