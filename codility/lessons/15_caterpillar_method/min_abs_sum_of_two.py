
def solution(A):
    A.sort()

    p, q, n = 0, len(A)-1, len(A)
    best_abs_sum = abs(A[p] + A[q])

    positive_start = 0
    while positive_start < n and A[positive_start] < 0:
        positive_start += 1

    # case 1, right to zero
    if positive_start < n:
        best_abs_sum = min(best_abs_sum,
            abs(A[positive_start] + A[positive_start]))

    # case 2, left to zero
    if positive_start - 1 >= 0:
        best_abs_sum = min(best_abs_sum,
            abs(A[positive_start-1] + A[positive_start-1]))

    #case 3, left and right
    while p < positive_start:
        best_abs_sum = min(best_abs_sum, abs(A[p] + A[q]))
        while q >= positive_start and abs(A[p]) < A[q]:
            best_abs_sum = min(best_abs_sum, abs(A[p] + A[q]))
            q -= 1
        p += 1

    return best_abs_sum
