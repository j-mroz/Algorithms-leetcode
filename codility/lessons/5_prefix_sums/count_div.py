# https://app.codility.com/programmers/lessons/5-prefix_sums/count_div/

def solution(A, B, K):
    first_divisible = (A + K - 1) // K * K
    last_divisible = B // K * K
    return 1 + (last_divisible - first_divisible)//K
