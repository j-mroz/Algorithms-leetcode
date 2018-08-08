# https://app.codility.com/programmers/lessons/5-prefix_sums/genomic_range_query/

class PrefixSumArray:

    def __init__(self, values):
        values = list(values)
        self.arr = [0] * (len(values) + 1)
        for (i, value) in enumerate(values):
            self.arr[i+1] = self.arr[i] + value

    def query_range(self, first, last):
        return self.arr[last+1] - self.arr[first]


def solution(S, P, Q):
    nucleotides_by_inpact = []
    for code in "ACGT":
        nucleotides_by_inpact += [PrefixSumArray(1 if x==code else 0 for x in S)]

    results = []

    for (first, last) in zip(P, Q):
        for inpact in range(4):
            if nucleotides_by_inpact[inpact].query_range(first, last) > 0:
                results += [inpact + 1]
                break

    return results
