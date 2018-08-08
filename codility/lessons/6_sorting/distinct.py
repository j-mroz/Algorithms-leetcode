# https://app.codility.com/programmers/lessons/6-sorting/distinct/

#
# this a fancy way to do:
#
# def solution(A):
#     return len(set(A))
def solution(A):
    A.sort();
    unique_numbers_count = 0

    for (i, number) in enumerate(A):
        if i+1 == len(A) or number != A[i+1]:
            unique_numbers_count += 1

    return unique_numbers_count
