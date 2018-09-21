from collections import deque

def solution(A, B):

    segments = deque(zip(A, B))
    non_overlapping_count = 0
    last_end = -1

    while segments:
        seg = segments.popleft()
        if seg[0] > last_end:
            non_overlapping_count += 1
            last_end = seg[1]

    return non_overlapping_count
