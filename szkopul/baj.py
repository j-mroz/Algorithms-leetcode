from collections import namedtuple
from dataclasses import dataclass
from itertools import groupby
import numpy as np

@dataclass
class Node:
    parent: int
    size: int

@dataclass
class Edge:
    src: int
    dst: int
    weight: int
    heavy: bool
    index: int

class DisjointSet:
    def __init__(self, size):
        self.nodes = [Node(i, 1) for i in range(size)]

    def find_root(self, x):
        while x != self.nodes[x].parent:
            parent = self.nodes[x].parent
            self.nodes[x].parent = self.nodes[parent].parent
            x = parent
        return x

    def connected(self, x, y):
        return self.find_root(x) == self.find_root(y)

    def connect(self, x, y):
        x, y = self.find_root(x), self.find_root(y)
        if self.nodes[x].size > self.nodes[y].size:
            x, y = y, x
        self.nodes[x].parent = y
        self.nodes[y].size += self.nodes[x].size


n, m = map(int, input().split())

vertices = DisjointSet(n + 1)

edges = np.array(
    [(*map(int, input().split()), i, False) for i in range(m)],
    dtype=[('src', np.int32), ('dst', np.int32), ('weight', np.int32),
           ('index', np.int32), ('heavy', np.bool)])
edges.sort(order='weight')

for _, edges_group in groupby(edges, lambda e: e['weight']):
    edges_group = list(edges_group)
    for edge in edges_group:
        if vertices.connected(edge['src'], edge['dst']):
            edge['heavy'] = True
    for edge in edges_group:
        vertices.connect(edge['src'], edge['dst'])

edges.sort(order='index')
for edge in edges:
    print("TAK" if not edge['heavy'] else "NIE")
