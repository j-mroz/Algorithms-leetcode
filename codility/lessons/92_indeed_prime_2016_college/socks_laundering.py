# https://app.codility.com/programmers/lessons/92-tasks_from_indeed_prime_2016_college_coders_challenge/socks_laundering/

from collections import Counter

def solution(K, C, D):
    clean_socks = Counter(C)
    dirty_socks = Counter(D)
    wash_machine_capacity = K

    # case 1: odds from dirty with odds from clean
    for (sock, dirty_count) in dirty_socks.items():
        if not wash_machine_capacity:
            break
        clean_count = clean_socks[sock] % 2 if sock in clean_socks else 0
        if dirty_count % 2 == 1 and clean_count % 2 == 1:
            clean_socks[sock] += 1
            dirty_socks[sock] -= 1
            wash_machine_capacity -= 1

    # case 2: odds from clean
    for (sock, clean_count) in clean_socks.items():
        if not wash_machine_capacity:
            break
        dirty_count = dirty_socks[sock] if sock in dirty_socks else 0
        if clean_count % 2 == 1 and dirty_count > 0:
            clean_socks[sock] += 1
            dirty_socks[sock] -= 1
            wash_machine_capacity -= 1

    # case 3: rest from dirty
    for (sock, dirty_count) in dirty_socks.items():
        if not wash_machine_capacity:
            break
        if dirty_count >= 2:
            move_count = min(dirty_count-dirty_count%2, wash_machine_capacity)
            clean_socks[sock] += move_count
            dirty_socks[sock] -= move_count
            wash_machine_capacity -= move_count

    return sum(count//2 for count in clean_socks.values())
