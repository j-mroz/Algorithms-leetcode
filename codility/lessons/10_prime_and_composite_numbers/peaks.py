# https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/peaks/start/ 

class PrefixSumArray:

    def __init__(self, values):
        values = list(values)
        self.arr = [0] * (len(values) + 1)
        for (i, value) in enumerate(values):
            self.arr[i+1] = self.arr[i] + value

    def query_range(self, first, last):
        return self.arr[last+1] - self.arr[first]


def is_peak(A, index):
    return 0 < index < len(A)-1 and A[index-1] < A[index] > A[index+1]


def solution(A):
    peaks = PrefixSumArray(int(is_peak(A, index)) for index,_ in enumerate(A))
    size = len(A)
    peaks_count = peaks.query_range(0, size-1)

    for blocks_count in range(peaks_count, 1, -1):
        if size % blocks_count == 0:
            block_size = size//blocks_count
            blocks_range = range(0, size, block_size)
            if all(peaks.query_range(i, i+block_size-1) for i in blocks_range):
                return blocks_count

    return int(peaks_count > 0)
