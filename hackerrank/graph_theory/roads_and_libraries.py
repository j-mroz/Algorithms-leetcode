#!/bin/python3

#
# https://www.hackerrank.com/challenges/torque-and-development/problem
#

import sys

def solve_roads_and_libraries(n, c_lib, c_road, cities):
    adjlist = [ [] for _ in range(n) ]

    def connect(u, v):
        adjlist[u-1].append(v-1)
        adjlist[v-1].append(u-1)

    visited = [ False for _ in range(n) ]

    def scc_vertex_count(u):
        vertex_count = 0
        if not visited[u]:
            visited[u] = True
            vertex_count = 1
            for v in adjlist[u]:
                vertex_count += scc_vertex_count(v)
        return vertex_count

    for u, v in cities:
        connect(u, v)

    cost = 0
    for vertex, _ in enumerate(adjlist):
        if not visited[vertex]:
            vertex_count = scc_vertex_count(vertex)
            edge_count = vertex_count - 1
            scc_cost = min(vertex_count * c_lib, edge_count * c_road + c_lib)
            cost += scc_cost

    return cost

if __name__ == "__main__":
    q = int(input().strip())
    for a0 in range(q):
        n, m, c_lib, c_road = input().strip().split(' ')
        n, m, c_lib, c_road = [int(n), int(m), int(c_lib), int(c_road)]
        cities = []
        for cities_i in range(m):
           cities_t = [int(cities_temp) for cities_temp in input().strip().split(' ')]
           cities.append(cities_t)
        result = solve_roads_and_libraries(n, c_lib, c_road, cities)
        print(result)
