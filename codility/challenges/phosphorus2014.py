from itertools import izip

WHITE = 0
BLACK = 1
GRAY = 2

class Node:
    def __init__(self, parrent, this, color):
        self.parrent = parrent
        self.this = this
        self.children = []
        self.color = color
        self.tree_color = color


def cell_group_dfs(p, u, adj_list, is_cell, visited):
    this = Node(p, u, int(is_cell[u]))
    if is_cell[u]:
        return this

    if visited[u]:
        return None
    visited[u] = True

    for v in adj_list[u]:
        if not visited[v]:
            x = cell_group_dfs(u, v, adj_list, is_cell, visited)
            if x:
                this.children.append(x)
                if x.tree_color == BLACK:
                    this.tree_color = BLACK

    return this


def leafs_count(u, adj_list):
    res = 0
    black_trees = 0
    white_trees = 0

    for v in u.children:
        r = leafs_count(v, adj_list)
        res += r
        if v.tree_color == BLACK:
            black_trees += 1
        elif v.tree_color == WHITE:
            white_trees += 1

    gray_trees = len(u.children) - black_trees - white_trees

    if black_trees >= 1 and white_trees >= 1:
        u.tree_color = GRAY
        res += 1
    elif gray_trees >= 1 and white_trees >= 1:
        u.tree_color = WHITE
    elif gray_trees >= 1 and black_trees == 0:
        u.tree_color = GRAY
    elif black_trees >= 1:
        u.tree_color = BLACK
    elif black_trees == 0 and white_trees >= 1:
        u.tree_color = WHITE

    if len(adj_list[u.this]) == 1 and black_trees >= 1:
        res += 1

    return res


def solution(A, B, C):
    N = len(A)
    adj_list = [[] for n in xrange(N+1)]
    for u, v in izip(A, B):
        adj_list[u].append(v)
        adj_list[v].append(u)

    visited = [False for n in xrange(N+1)]
    cells = visited[:]
    for c in C:
        cells[c] = True

    for u, adj in enumerate(adj_list):
        if len(adj) == 1:
            if cells[u]:
                return -1

    guards = 0
    for c in C:
        for u in adj_list[c]:
            root = cell_group_dfs(None, u, adj_list, cells, visited)
            if root:
                guards += leafs_count(root, adj_list)

    return guards
