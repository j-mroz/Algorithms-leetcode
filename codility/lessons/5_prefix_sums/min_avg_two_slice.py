# https://app.codility.com/programmers/lessons/5-prefix_sums/min_avg_two_slice/

class PrefixSumArray:

    def __init__(self, values):
        values = list(values)
        self.arr = [0] * (len(values) + 1)
        for (i, value) in enumerate(values):
            self.arr[i+1] = self.arr[i] + value

    def query_range(self, first, last):
        return self.arr[last+1] - self.arr[first]

def solution(A):
    sums = PrefixSumArray(A)

    min_avg, min_avg_start = 10_001, 0

    end = len(A)
    for s in range(end - 1):

        avg1 = sums.query_range(s, s+1)/2
        if avg1 < min_avg:
            min_avg = avg1
            min_avg_start = s

        if s+2 >= end:
            continue

        avg2 = sums.query_range(s, s+2)/3
        if avg2 < min_avg:
            min_avg = avg2
            min_avg_start = s

    return min_avg_start
