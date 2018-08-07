# https://app.codility.com/programmers/lessons/2-arrays/odd_occurrences_in_array/

from collections import Counter

def solution(A):
    occurrences = Counter(A)
    for (value, count) in occurrences.items():
        if count%2 == 1:
            return value
    return -1
