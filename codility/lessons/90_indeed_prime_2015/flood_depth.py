# https://app.codility.com/programmers/lessons/90-tasks_from_indeed_prime_2015_challenge/flood_depth/

def solution(A):
    best_depth = 0
    lowest, highest = A[0], A[0]

    for i in range(1, len(A)):
        best_depth = max(best_depth, min(highest, A[i])-lowest)
        if A[i] < lowest:
            lowest = A[i]
        if A[i] >= highest:
            lowest, highest = A[i], A[i]
            
    return best_depth
