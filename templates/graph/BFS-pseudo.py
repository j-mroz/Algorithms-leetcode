# G - graf
# s - wierzcholek startowy
# WHITE - wierzcholek nieodwiedzony
# GRAY - wierzcholek zakolejkowany
# BLACK - wierzchołek przetworzonu

def bfs(G, start):

    for v in vertices_of(G):
        set_vertex(v, color=WHITE, distance=INFINITY, parent=None)
    set_vertex(start, color=GRAY, distance=0, parent=None)

    # While queue is not empty
    queue = [ start ]
    while queue:
        u = queue.pop(0)
        for v in adjacent_to(u):
            if color_of(v) is WHITE:
                set_vertex(v, color=GRAY, distance=distance_of(u)+1, parent=u)
                queue.append(v)
        set_vertex(u, color=BLACK)









