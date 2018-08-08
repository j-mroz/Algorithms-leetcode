# https://app.codility.com/programmers/lessons/7-stacks_and_queues/nesting/

def solution(S):
    brackets_stack = []

    for bracket in S:
        if bracket == '(':
            brackets_stack.append(bracket)
        elif not brackets_stack:
            return 0
        else:
            brackets_stack.pop()

    if not brackets_stack:
        return 1
    return 0
