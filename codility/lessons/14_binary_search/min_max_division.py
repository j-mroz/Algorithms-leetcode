def check_sum(A, K, candidate_sum):
    slice_sum, slice_count = 0, 1
    for a in A:
        if a > candidate_sum:
            return False
        if slice_sum + a <= candidate_sum:
            slice_sum += a
        else:
            slice_sum = a
            slice_count += 1
    return slice_count <= K


def solution(K, M, A):
    max_sum = sum(A)
    min_element = min(A)
    candidate_sum = min_element

    while candidate_sum < max_sum:
        if check_sum(A, K, candidate_sum):
            return candidate_sum
        candidate_sum += 1

    return candidate_sum

#
def is_large_sum(A, K, candidate_sum):
    slice_sum, slice_count = 0, 1
    for a in A:
        if a > candidate_sum:
            return False
        if slice_sum + a <= candidate_sum:
            slice_sum += a
        else:
            slice_sum = a
            slice_count += 1
    return slice_count <= K


def solution(K, M, A):
    low, hi = min(A), sum(A)

    while hi - low > 0:
        candidate_sum = (low + hi) // 2
        if is_large_sum(A, K, candidate_sum):
            hi = candidate_sum
        else:
            low = candidate_sum + 1

    return hi
