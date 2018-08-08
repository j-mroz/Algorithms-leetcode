# https://app.codility.com/programmers/lessons/7-stacks_and_queues/brackets/

def solution(S):
    maching_brackets = {"{":"}", "(":")", "[":"]"}
    brackets_stack = []

    for bracket in S:
        if bracket in "({[":
            brackets_stack.append(bracket)
        else:
            if not brackets_stack:
                return 0

            start_bracket = brackets_stack.pop()
            if bracket != maching_brackets[start_bracket]:
                return 0

    if not brackets_stack:
        return 1
    return 0
