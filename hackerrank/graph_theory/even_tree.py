#!/bin/python3
from collections import defaultdict

def solve_even_tree(adjlist, root):
    visited = set()
    cut_count = 0

    def visit(adjlist, node):
        nonlocal cut_count
        visited.add(node)
        descendant_count = 0
        for child_node in adjlist[node]:
            if child_node not in visited:
                descendant_count += visit(adjlist, child_node)
        if descendant_count > 0 and (descendant_count+1) % 2 == 0:
            cut_count += 1
            return 0
        return descendant_count + 1

    visit(adjlist, root)

    return cut_count-1

if __name__ == '__main__':
    tree_nodes, tree_edges = map(int, input().split())

    adjlist = [ []  for _ in range(tree_nodes) ]
    in_degrees = defaultdict(int)

    for _ in range(tree_edges):
        u, v = [int(i)-1 for i in input().split()]
        adjlist[u].append(v)
        adjlist[v].append(u)
        in_degrees[u] += 1
        in_degrees[v] += 1

    root = next((vertex for vertex, degree in in_degrees.items() if degree == 1))
    cut_count = solve_even_tree(adjlist, root)
    print(cut_count)

    
