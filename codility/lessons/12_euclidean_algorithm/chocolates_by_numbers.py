# https://app.codility.com/programmers/lessons/12-euclidean_algorithm/chocolates_by_numbers/

def gcd(a, b):
    while b > 0:
        a, b = b, a % b
    return a

def solution(N, M):
    return N // gcd(N, M)
