# https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/flags/

def is_peak(A, index):
    return 0 < index < len(A)-1 and A[index-1] < A[index] > A[index+1]

def min_distance_peaks_count(peaks, min_distance):
    if not peaks:
        return 0

    peaks_count = 0

    index = 0
    while index < len(peaks):
        next_index = index + 1
        while next_index < len(peaks) and peaks[index] + min_distance > peaks[next_index]:
            next_index += 1
        if next_index < len(peaks):
            peaks_count += 1
        index = next_index

    return peaks_count


def solution(A):
    peaks_bitmap = (is_peak(A, index) for index, _ in enumerate(A))
    peaks = [peak for peak, _ in filter(lambda x: x[1], enumerate(peaks_bitmap))]

    # Intead of looking for maximum k iteratievly do a bisection.
    start_k, end_k = 1, len(peaks) + 1
    while start_k < end_k:
        mid_k = (start_k + end_k) // 2
        if mid_k <= min_distance_peaks_count(peaks, mid_k):
            start_k = mid_k + 1
        else:
            end_k = mid_k

    k = start_k - 1
    return k
