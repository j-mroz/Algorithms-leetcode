# https://app.codility.com/programmers/lessons/1-iterations/

def solution(N):
    binary_sequence = bin(N)[2:]
    longest_zeros_gap, current_zeros_gap = 0, 0

    for bit in binary_sequence):
        if bit == '0':
            current_zeros_gap += 1
        else:
            longest_zeros_gap = max(longest_zeros_gap, current_zeros_gap)
            current_zeros_gap = 0

    return longest_zeros_gap
