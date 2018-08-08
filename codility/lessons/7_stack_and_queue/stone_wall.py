# https://app.codility.com/programmers/lessons/7-stacks_and_queues/stone_wall/

def solution(H):
    height_stack = []
    blocks_used = 0

    for wall_height in H:

        while height_stack and height_stack[-1] > wall_height:
            height_stack.pop()

        if not height_stack or height_stack[-1] < wall_height:
            height_stack.append(wall_height)
            blocks_used += 1

    return blocks_used
