# https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/count_factors/

def solution(N):
    sqrt_n = int(N**0.5)
    sqrt_n_range = range(1, sqrt_n+1)
    is_factor = lambda x: N%x == 0
    return 2*len(list(filter(is_factor, sqrt_n_range))) - int(sqrt_n**2 == N)
