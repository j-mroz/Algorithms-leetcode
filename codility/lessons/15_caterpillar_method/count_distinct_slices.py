
def solution(M, A):
    counter = [0] * (M + 1)

    start, end, n = 0, 0, len(A)
    distinct_slice_count = 0

    while start < n:
        while end < n and counter[A[end]] == 0:
            counter[A[end]] += 1
            end += 1
        distinct_slice_count += end - start
        counter[A[start]] -= 1
        start += 1

    return min(distinct_slice_count, 1_000_000_000)
