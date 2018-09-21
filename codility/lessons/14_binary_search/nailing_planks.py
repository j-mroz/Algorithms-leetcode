
def all_planks_nailed(starts, ends, nails):
    max_point = max(max(ends), max(nails))

    prefix_sums = [0] * (max_point + 2)
    for nail in nails:
        prefix_sums[nail+1] += 1
    for index in range(1, len(prefix_sums)):
        prefix_sums[index] += prefix_sums[index-1]

    for start, end in zip(starts, ends):
        nails_in_plank = prefix_sums[end+1] - prefix_sums[start]
        if nails_in_plank == 0:
            return False
    return True

def solution(starts, ends, nails):

    low, hi = 1, len(nails) + 1
    while low < hi:
        mid = (low + hi) // 2
        if all_planks_nailed(starts, ends, nails[:mid]):
            hi = mid
        else:
            low = mid + 1

    if hi <= len(nails):
        return hi
    return -1
