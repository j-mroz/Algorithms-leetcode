
# https://app.codility.com/programmers/lessons/13-fibonacci_numbers/fib_frog/

UNREACHABLE = 1_000_007


def fibonaci_range(s, n):
    result = []
    a, b = 0, 1
    while a < n:
        # add only if in range, skip second 1
        if a >= s and (a, b) != (1, 2):
            result += [a]
        a, b = b, a + b
    return result


def solution(path):
    # path[0] is starting shore, path[-1] is destination shore
    path = [1] + path + [1]
    jumps = [UNREACHABLE] * (len(path))
    jumps[0] = 0
    fibonaci_numbers = fibonaci_range(1, len(path))

    for pos in range(1, len(path)):
        if not path[pos]:
            continue
        for jump_length in fibonaci_numbers:
            prev_pos = pos - jump_length
            if prev_pos < 0:
                break
            if path[prev_pos]:
                jumps[pos] = min(jumps[pos], jumps[prev_pos] + 1)

    if jumps[-1] == UNREACHABLE:
        return -1
    return jumps[-1]
