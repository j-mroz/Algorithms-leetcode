
def solution(A):

    results = [0] * len(A)
    results[0] = A[0]

    for pos, _ in enumerate(A):
        if pos > 0:
            results[pos] = A[pos] + max(results[max(0, pos-6):pos])

    return results[-1]
