# https://app.codility.com/programmers/lessons/4-counting_elements/perm_check/

from collections import Counter

def solution(A):
    occurences = Counter(A)
    start, end = 1, len(A) + 1
    for number in range(start, end):
        count = occurences.get(number)
        if count != 1:
            return 0
    return 1
