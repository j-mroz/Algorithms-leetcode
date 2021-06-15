# G = [
#     [(1, 16), (2, 13)],     # s
#     [(3, 12), (2, 10)],     # v1
#     [(1, 4), (4, 14)],      # v2
#     [(2, 9), (-1, 20)],     # v3
#     [(3, 7),],              # v4
#     [(4, 4),],              # t
# ]

# G = [
#     [(1, 1), (2, 1), (3, 1)],   # s
#     [(4, 1)],                   # v1
#     [(5, 1)],      # v2
#     [(5, 1)],     # v3
#     [(-1, 1),],              # v4
#     [(-1, 1),],              # t
#     [(6,1)]
# ]

G = [
    [(1, 1), (2, 1), (3, 1), (4, 1), (5, 1)],   # s

    [(5+2, 1), (5+1, 1)],
    [(5+2, 1), (5+3, 1), (5+4, 1)],
    [(5+1, 1), (5+5, 1)],
    [(5+1, 1), (5+2, 1), (5+5, 1)],
    [(5+2, 1)],

    [(-1, 1)],
    [(-1, 1)],
    [(-1, 1)],
    [(-1, 1)],
    [(-1, 1)],

    [(11, 1)]
]


def residual_paths(G, F, s, t):

    def adj_residual(u):
        for (v, w) in G[u]:
            if not visited[v] and F[(u, v)] < w:
                yield (v, w)

    def dfs(u, p=[]):

        for v, w in adj_residual(u):
            visited[v] = True
            ret = dfs(v, p + [(u, v, w)])
            if ret:
                return ret
        return p if (u == t) else None

    while True:
        visited = [False for v in G]
        p = dfs(s)
        if not p:
            break
        yield p


def ford_fulkerson(G):
    flows = dict()
    edges = list((u, v, c) for (u, u_edges) in enumerate(G) for (v, c) in u_edges)
    print edges
    for (u, v, _) in edges:
        flows[(u, v)] = 0
        flows[(v, u)] = 0

    for path in residual_paths(G, flows, 0, -1):
        path_capacity =  min(w for _, _ , w in path)
        for u, v, _ in path:
            flows[(u, v)] += path_capacity
            flows[(v, u)] = -flows[(u, v)]
    return sum(flows[(0, v)] for v, w in G[0])
        

if __name__ == "__main__":
    print ford_fulkerson(G)