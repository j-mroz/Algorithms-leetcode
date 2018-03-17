#!/bin/python3

import sys

def solve_journey_to_moon(n, astronaut_pairs):
    adjacent = make_adj_list(n, astronaut_pairs)
    visited = make_visited_list(n)

    scc_counts = [count_connected(adjacent, visited, u) for u in range(n)]
    scc_counts = [count for count in scc_counts if count > 0]
    suffix_sums = make_suffix_sums(scc_counts)

    ret = sum(scc_counts[i] * suffix_sums[i+1] for i in range(len(scc_counts)-1))

    return ret

def make_adj_list(vertex_count, edges):
    adjlist = [ [] for _ in range(vertex_count) ]
    for u, v in edges:
        adjlist[u].append(v)
        adjlist[v].append(u)
    return adjlist

def make_visited_list(vertex_count):
    return [ False for _ in range(vertex_count) ]

def count_connected(adjlist, visited, u):
    if visited[u]:
        return 0
    visited[u] = True
    count = 1
    visit_stack = [x for x in adjlist[u] if not visited[x]]
    while len(visit_stack) > 0:
        v = visit_stack.pop()
        if not visited[v]:
            visited[v] = True
            count += 1
            visit_stack += [x for x in adjlist[v] if not visited[x]]
    return count

def make_suffix_sums(numbers):
    suffix_sums = numbers[:]
    for i in reversed(list(range(0, len(numbers)-1))):
        suffix_sums[i] += suffix_sums[i+1]
    return suffix_sums


if __name__ == "__main__":
    n, p = input().strip().split(' ')
    n, p = [int(n), int(p)]
    astronaut = []
    for astronaut_i in range(p):
       astronaut_t = [int(astronaut_temp) for astronaut_temp in input().strip().split(' ')]
       astronaut.append(astronaut_t)
    result = solve_journey_to_moon(n, astronaut)
    print(result)
