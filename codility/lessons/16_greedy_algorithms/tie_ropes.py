def solution(K, A):

    rope_length = 0
    ropes_count = 0

    for a in A:
        rope_length += a
        if rope_length >= K:
            rope_length = 0
            ropes_count += 1

    return ropes_count
