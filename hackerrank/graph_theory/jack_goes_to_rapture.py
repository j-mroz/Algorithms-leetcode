#!/bin/python3
import heapq

def solve_jack_goes_to_rapture(N, adjlist):
    mst = prim_mst(adjlist, 0)
    edge_costs = {(u, v):c for u, uadj in enumerate(adjlist) for v, c in uadj}

    x = N-1
    if not x in mst:
        return "NO PATH EXISTS"

    cost = -1
    while mst[x] != x:
        cost = max(cost, edge_costs[(mst[x], x)])
        x = mst[x]
    return cost

def prim_mst(adjlist, src):
    mst = dict()
    queue = []
    heapq.heappush(queue, (0, 0, src))

    while queue:
        ucost, uparent, u = heapq.heappop(queue)
        if u in mst:
            continue
        mst[u] = uparent

        adj_not_visited = ((c, x)  for (x, c) in adjlist[u] if not x in mst)
        for vcost, v in adj_not_visited:
            heapq.heappush(queue, (vcost, u, v))
            heapq.heapreplace

    return mst

if __name__ == '__main__':
    vertex_count, edge_count = [int(i) for i in input().split()]
    adjlist = [ [] for _ in range(vertex_count) ]
    for _ in range(edge_count):
        u, v, c = [int(i) for i in input().split()]
        adjlist[u-1].append((v-1, c))
        adjlist[v-1].append((u-1, c))

    result = solve_jack_goes_to_rapture(vertex_count, adjlist)
    print(result)
