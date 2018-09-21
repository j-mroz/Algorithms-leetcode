
# this works too
#def solution(A):
#    return len(set(abs(a) for a in A))

def abs_equls(a, b):
    return abs(a) == abs(b)

def solution(A):
    start, end = 0, len(A) - 1
    count = 0

    while start <= end:
        value = max(abs(A[start]), abs(A[end]))
        while start <= end and abs_equls(A[start], value):
            start += 1
        while start <= end and abs_equls(A[end], value):
            end -= 1
        count += 1

    return count
