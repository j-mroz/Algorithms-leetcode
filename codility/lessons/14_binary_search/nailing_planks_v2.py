from bisect import bisect_left, bisect_right

def lower_bound(arr, x):
    return bisect_left(arr, x)
    # low, hi = 0, len(arr)
    # while low < hi:
    #     mid = (low + hi) // 2
    #     if x <= arr[mid]:
    #         hi = mid
    #     else:
    #         low = mid + 1
    # return hi


def upper_bound(arr, x):
    return bisect_right(arr, x)
    # low, hi = 0, len(arr)
    # while low < hi:
    #     mid = (low + hi) // 2
    #     if x < arr[mid]:
    #         hi = mid
    #     else:
    #         low = mid + 1
    # return hi

def all_planks_nailed(planks, nails):
    nails.sort()
    nailed_planks_count = 0

    for plank in planks:
        plank_start, plank_end = plank
        nails_start = lower_bound(nails, plank_start)
        nails_end = upper_bound(nails, plank_end)
        if nails_start < nails_end:
            nailed_planks_count += 1

    return nailed_planks_count == len(planks)


def solution(starts, ends, nails):
    planks = list(zip(starts, ends))
    planks.sort()

    low, hi = 0, len(nails) + 1
    while low < hi:
        mid = (low + hi) // 2
        if all_planks_nailed(planks, nails[:mid]):
            hi = mid
        else:
            low = mid + 1

    if hi <= len(nails):
        return hi
    return -1
