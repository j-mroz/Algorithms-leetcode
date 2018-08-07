# https://app.codility.com/programmers/lessons/3-time_complexity/frog_jmp/

def solution(X, Y, D):
    # X + jumps*D >= Y
    # jumps*D >= Y - X
    # jumps >= (Y - X) / D
    jumps = (Y - X) // D
    if X + jumps*D < Y:
        jumps += 1
    return jumps
