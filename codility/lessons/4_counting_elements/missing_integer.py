# https://app.codility.com/programmers/lessons/4-counting_elements/missing_integer/

from collections import Counter

def solution(A):
    occurrences = Counter(A)
    start, end  = 1, len(A)+1
    for number in range(start, end):
        if number not in occurrences:
            return number
    return end
