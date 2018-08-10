# https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/min_perimeter_rectangle/

def solution(N):
    min_perimeter = 2*N + 2
    lower, upper = 1, int(N**0.5)
    for number in range(lower, upper+1):
        if N % number == 0:
            min_perimeter = min(min_perimeter, 2*(number + N//number))
    return min_perimeter
