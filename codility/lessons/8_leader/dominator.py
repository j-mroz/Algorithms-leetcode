# https://app.codility.com/programmers/lessons/8-leader/dominator/

def solution(A):

    leader, leader_index, leader_count = None, -1, 0

    for (index, value) in enumerate(A):
        if leader_count == 0:
            leader, leader_index, leader_count = value, index, 1
        elif leader == value:
            leader_count += 1
        else:
            leader_count -= 1

    if A.count(leader) > len(A)//2:
        return leader_index
    return -1
