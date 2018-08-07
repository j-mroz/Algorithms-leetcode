# https://app.codility.com/programmers/lessons/3-time_complexity/tape_equilibrium/

def solution(A):
    minimal_diff = len(A) * 100000 + 1
    partial, remaining = 0, sum(A)
    for number in A[:-1]:
        partial += number
        remaining -= number
        diff = abs(partial - remaining)
        minimal_diff = min(minimal_diff, diff)
    return minimal_diff
