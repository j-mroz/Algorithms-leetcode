# https://app.codility.com/programmers/lessons/9-maximum_slice_problem/max_slice_sum/

def solution(A):
    sum_ending, max_sum = A[0], A[0]
    for a in A[1:]:
        sum_ending = max(a, sum_ending + a)
        max_sum = max(max_sum, sum_ending)
    return max_sum
