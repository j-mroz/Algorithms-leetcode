
def solution(A):

    if len(A) == 0:
        return 0

    A = [abs(a) for a in A]
    results = {A[0]}
    max_new_sum = max(A) ** 2

    # Facts:
    # (1) If the array has only unique absolute numbers then max sum must be
    # less than M ** 2, where M == max(A) (actually M*(M-1)/2).
    # If there are repetitions of new_sums, then actual sum is higher,
    # but two repetitions negates each other (note: you choose sign for each value).
    # Thus M ** 2 will be max partial sum we're willing to consider.
    # (2) There is always a total sum less or equal to 100.
    # (3) That sum can be reached by adding or substracting values from
    # smallers problem that has sum less than M*(M-1)/2) + 1.

    for i in range(1, len(A)):
        new_results = set()
        for prev_sum in results:
            new_sum = abs(prev_sum + A[i])
            if new_sum < max_new_sum:
                new_results.add(new_sum)
            new_sum = abs(prev_sum - A[i])
            if new_sum < max_new_sum:
                new_results.add(new_sum)
        results = new_results

    if results:
        return min(results)

    # unreachable if input is valid
    return -1
