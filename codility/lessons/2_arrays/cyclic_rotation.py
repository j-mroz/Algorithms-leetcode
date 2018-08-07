# https://app.codility.com/programmers/lessons/2-arrays/cyclic_rotation/

def rotated(arr, k):
    if len(arr) == 0:
        return arr
    k %= len(arr)
    rotated = arr[-k:] + arr[:-k]
    return rotated

def solution(A, K):
    return rotated(A, K)
