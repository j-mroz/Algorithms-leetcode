# https://app.codility.com/programmers/lessons/4-counting_elements/frog_river_one/

def solution(fields_count, leaf_fall_timeline):
    unknown_time = -1
    leaf_fall_time = [unknown_time] * fields_count

    for (second, leaf) in enumerate(leaf_fall_timeline):
        if leaf_fall_time[leaf-1] == -1:
            leaf_fall_time[leaf-1] = second

    if unknown_time in leaf_fall_time:
        return unknown_time
    return max(leaf_fall_time)
