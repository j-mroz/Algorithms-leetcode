# https://app.codility.com/programmers/lessons/91-tasks_from_indeed_prime_2016_challenge/rectangle_builder_greater_area/ 

from bisect import bisect_left
from collections import Counter

def solution(A, X):
    counter = {val:count for val,count in Counter(A).items() if count >= 2}
    A = sorted(val for val in counter)
    n = len(A)

    rectangles_count = 0

    for i, a in enumerate(A):
        j = bisect_left(A, X/a, lo=i+1)
        rectangles_count += n - j
        if a * a >= X and counter[a] >= 4:
            rectangles_count += 1

    if rectangles_count > 1_000_000_000:
        return -1
    return rectangles_count
