# https://app.codility.com/programmers/lessons/8-leader/equi_leader/

def solution(A):

    leader, leader_index, leader_count = None, -1, 0

    for (index, value) in enumerate(A):
        if leader_count == 0:
            leader, leader_index, leader_count = value, index, 1
        elif leader == value:
            leader_count += 1
        else:
            leader_count -= 1

    leader_count = A.count(leader)
    if leader_count <= len(A)//2:
        return 0

    left_leaders, right_leaders = 0, leader_count
    left_size, right_size = 0, len(A)
    equi_leaders_count = 0

    for (index, value) in enumerate(A[:-1]):
        left_size += 1
        right_size -= 1

        if value == leader:
            left_leaders += 1
            right_leaders -= 1

        if left_leaders > left_size//2 and right_leaders > right_size//2:
            equi_leaders_count += 1

    return equi_leaders_count
