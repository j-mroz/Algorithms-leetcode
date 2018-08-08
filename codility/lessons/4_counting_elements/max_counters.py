# https://app.codility.com/programmers/lessons/4-counting_elements/max_counters/

class CounterBank:
    def __init__(self, bank_size):
        self.counters = [0] * bank_size
        self.min_value = 0
        self.max_value = 0

    def increase(self, x):
        x -= 1
        value = max(self.min_value, self.counters[x]) + 1
        self.counters[x] = value
        self.max_value = max(self.max_value, self.counters[x])

    def maximize(self):
        self.min_value = self.max_value

    def values(self):
        for (i, value) in enumerate(self.counters):
            self.counters[i] = max(self.min_value, value)
        return self.counters

def solution(N, A):
    counters = CounterBank(N)

    for operation_code in A:
        if 1 <= operation_code <= N:
            counters.increase(operation_code)
        elif operation_code == N+1:
            counters.maximize()
        else:
            raise ValueError("illegal operation code: " + operation_code)

    return counters.values()
