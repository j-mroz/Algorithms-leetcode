# https://app.codility.com/programmers/lessons/9-maximum_slice_problem/max_double_slice_sum/

def solution(A):
    max_left_endings, max_right_endings = [0] * len(A), [0] * len(A)

    max_ending = 0
    for (index, value) in enumerate(A[1:-1]):
        index += 1
        max_ending = max(0, max_ending + value)
        max_left_endings[index] = max_ending

    max_ending = 0
    for (index, value) in reversed(list(enumerate(A[1:-1]))):
        index += 1
        max_ending = max(0, max_ending + value)
        max_right_endings[index] = max_ending

    max_double_slice = 0
    for (index, _) in enumerate(A[1:-1]):
        index += 1
        double_slice = max_left_endings[index-1] + max_right_endings[index+1]
        max_double_slice = max(max_double_slice, double_slice)

    return max_double_slice
