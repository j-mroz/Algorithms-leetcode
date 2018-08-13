# https://app.codility.com/programmers/lessons/11-sieve_of_eratosthenes/count_semiprimes/

from bisect import bisect_left, bisect_right
from math import sqrt


def primes_sieve(N):
    primes = [True] * (N + 1)
    primes[0] = primes[1] = False
    for i in range(2, int(sqrt(N)) + 1):
        if primes[i]:
            for k in range(i * i, N + 1, i):
                primes[k] = False
    return primes


def primes_range(N):
    return [num for num, is_prime in enumerate(primes_sieve(N)) if is_prime]


def semiprimes_range(N, primes):
    semiprimes = []
    q = bisect_left(primes, 2)
    while p < len(primes):
        q = bisect_left(primes, primes[p])
        while q < len(primes) and primes[p] * primes[q] <= N:
            semiprimes += [primes[p] * primes[q]]
            q += 1
        p += 1
    semiprimes.sort()
    return semiprimes


def solution(N, P, Q):
    primes = primes_range(N)
    semiprimes = semiprimes_range(N, primes)

    result = []
    for p, q in zip(P, Q):
        start = bisect_left(semiprimes, p)
        end = bisect_right(semiprimes, q)
        result += [end - start]

    return result
