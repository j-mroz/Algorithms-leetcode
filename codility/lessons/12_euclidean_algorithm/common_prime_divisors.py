# https://app.codility.com/programmers/lessons/12-euclidean_algorithm/common_prime_divisors/

from math import gcd

def non_common_divisor(value, common):
    """
    Returns value divisor that does not divide common or 1 if all factors were in common.
    """

    prev, value = value, value // gcd(value, common)
    while value != prev:
        prev, value = value, value // gcd(value, common)
    return value

def solution(A, B):
    result = 0
    for a, b in zip(A, B):
        common = gcd(a, b)
        a = non_common_divisor(a, common)
        b = non_common_divisor(b, common)
        if a == b == 1:
           result += 1
    return result
