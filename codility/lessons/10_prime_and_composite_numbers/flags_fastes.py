# https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/flags/

def next_peak_array(arr):
    size = len(arr)
    next_peak = [index if is_peak(arr, index) else size for index, _ in enumerate(arr)]
    for index in reversed(range(0, size-1)):
        if next_peak[index] == size:
            next_peak[index] = next_peak[index + 1]
    return next_peak

def is_peak(A, index):
    return 0 < index < len(A)-1 and A[index-1] < A[index] > A[index+1]

def advance_peak(next_peak, index, k):
    if index + k >= len(next_peak):
        return len(next_peak)
    return next_peak[index + k]

def solution(A):
    next_peak = next_peak_array(A)
    size = len(next_peak)
    
    k = 0
    while k * (k - 1) <= size:
        peak_index, peaks_count = next_peak[0], 0
        while peak_index < size and peaks_count < k:
            peak_index = advance_peak(next_peak, peak_index, k)
            peaks_count += 1
        if peaks_count < k:
            break
        k += 1

    return k - 1
