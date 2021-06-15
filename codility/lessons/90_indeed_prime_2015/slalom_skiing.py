# https://app.codility.com/programmers/lessons/90-tasks_from_indeed_prime_2015_challenge/slalom_skiing/

class BinaryIndexedTree:
    def __init__(self, size):
        self.nodes = [0] * (size + 1)

    def set_max(self, index, val):
        index += 1
        while index < len(self.nodes):
            self.nodes[index] = max(self.nodes[index], val)
            index += self.lsb(index)

    def query_max(self, index):
        result = 0
        index += 1
        while index > 0:
            result = max(result, self.nodes[index])
            index -= self.lsb(index)
        return result

    def lsb(self, index):
        return index & (-index)


def compress_values(arr):
    vi_arr = sorted((val,i) for i,val in enumerate(arr))
    inv_arr = ((i,new_val) for new_val,(val,i) in enumerate(vi_arr))
    compressed = [new_val for i,new_val in sorted(inv_arr)]
    return compressed


def solution(A):
    A = compress_values(A)
    max_a = max(A)

    dp = [[-1 for _ in A] for _ in range(3)]
    bit = [BinaryIndexedTree(max(A)) for _ in range(3)]

    for i in range(len(A)):
        longest = bit[0].query_max(A[i]-1) + 1
        bit[0].set_max(A[i], longest)
        dp[0][i] = longest

    for i in range(len(A)):
        longest = max(dp[0][i], bit[1].query_max(max_a-A[i]-1) + 1)
        bit[1].set_max(max_a-A[i], longest)
        dp[1][i] = longest

    for i in range(len(A)):
        longest = max(dp[1][i], bit[2].query_max(A[i]-1) + 1)
        bit[2].set_max(A[i], longest)
        dp[2][i] = longest

    return max(max(dp[2]), max(dp[1]), max(dp[0]))
