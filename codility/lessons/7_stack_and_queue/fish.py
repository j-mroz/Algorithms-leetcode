# https://app.codility.com/programmers/lessons/7-stacks_and_queues/fish/

UPSTREAM, DOWNSTREAM = 0, 1

def solution(A, B):

    fishes_alive = len(A)
    downstream_stack = []

    for (fish_size, direction) in zip(A, B):

        if direction == DOWNSTREAM:
            downstream_stack.append(fish_size)
            continue

        while downstream_stack and fish_size > downstream_stack[-1]:
            fishes_alive -= 1
            downstream_stack.pop()

        if downstream_stack and fish_size < downstream_stack[-1]:
            fishes_alive -= 1

    return fishes_alive
