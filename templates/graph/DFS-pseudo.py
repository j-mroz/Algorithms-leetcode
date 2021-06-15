T = 0
def time():
    global T
    T += 1
    return T

def dfs(G):
    for v in vertices_of(G):
        set_vertex(v, color=WHITE, parrent=None)

    for v in vertices_of(G):
        dfs_visit(v)


def dfs_visit(v):
    global time
    time  += 1
    set_vertex(v, color=GRAY, visit_time=time)

    for u in adjacent_to(u):
        if color_of(u) is WHITE:
            set_vertex(u, parrent=v)
            dfs_visit(u)
    time  += 1
    set_vertex(u, color=BLACK, finish_time=time)