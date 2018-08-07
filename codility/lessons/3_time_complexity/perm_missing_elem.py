# https://app.codility.com/programmers/lessons/3-time_complexity/perm_missing_elem/


def solution(numbers):
    n = len(numbers) + 1
    expected_sum = (1 + n) * n // 2
    actual_sum = sum(numbers)
    return expected_sum - actual_sum
