from math import log, floor
from sys import stdin, stdout

def bin_digits(n):
    if n <= 1:
        return 1
    return floor(log(n, 2) + 1)

def concat_digits_len(num):
    depth = 0
    total = 0
    bin_counter = 1
    while total + (2 ** depth) <= num:
        # bin_counter +=  (2 ** depth) * len(bin(total + 1)[2:])
        level_size = (2 ** depth)
        bin_counter += level_size * bin_digits(total + 1)
        total += level_size
        depth += 1
    bin_counter += bin_digits(total + 1) * (num - total)

    return bin_counter

num_tests = int(stdin.readline())
# num_tests = int(input())
for _ in range(num_tests):
    num = int(stdin.readline())
    len = concat_digits_len(num)
    print(len)
