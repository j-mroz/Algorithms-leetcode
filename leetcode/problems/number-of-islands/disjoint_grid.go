package main

import "fmt"

type GridIndex struct {
    i int
    j int
}

func equal(a, b GridIndex) bool {
    return (a.i == b.i) && (a.j == b.j)
}

type DisjointGrid struct {
    parent  [][]GridIndex
    count   int
}

func NewDisjointGrid(grid [][]byte) *DisjointGrid {
    this := new(DisjointGrid)
    this.parent = make([][]GridIndex, len(grid))

    for i, _ := range grid {
        this.parent[i] = make([]GridIndex, len(grid[i]))
        for j, value := range grid[i] {
            this.parent[i][j] = GridIndex{i, j}
            if value != '0' {
                this.count++
            }
        }
    }

    return this
}

func (this *DisjointGrid) getParent(idx GridIndex) GridIndex {
    return this.parent[idx.i][idx.j]
}

func (this *DisjointGrid) setParent(dst GridIndex, src GridIndex) {
    this.parent[dst.i][dst.j] = this.parent[src.i][src.j]
}

func (this *DisjointGrid) find(idx GridIndex) GridIndex {
    // Find root element of idx.
    root := idx
    for parent := this.getParent(root); !equal(root, parent); {
        root = parent
        parent = this.getParent(root)
    }

    // Compress path.
    for element := idx; !equal(element, root); {
        parent := this.getParent(element)
        this.setParent(element, root)
        element = parent
    }

    return root;
}


func (this *DisjointGrid) Connect(a, b GridIndex) {
    a, b = this.find(a), this.find(b)
    if !equal(a, b) {
        this.setParent(b, a)
        this.count--
    }
}

func (this *DisjointGrid) AreConnected(a, b GridIndex) bool {
    return this.find(a) == this.find(b)
}

func numIslands(grid [][]byte) int {
    set := NewDisjointGrid(grid)

    for i, _ := range grid {
        for j, value := range grid[i] {
            if value == '0' {
                continue
            }

            idx     := GridIndex{i,    j}
            upIdx   := GridIndex{i-1,  j}
            leftIdx := GridIndex{i,  j-1}

            if upIdx.i >= 0 && grid[upIdx.i][upIdx.j] != '0' {
                set.Connect(idx, upIdx)
            }
            if leftIdx.j >= 0 && grid[leftIdx.i][leftIdx.j] != '0' {
                set.Connect(idx, leftIdx)
            }
        }
    }

    return set.count
}

func main() {
    input := [][]byte{
        []byte("11110"),
        []byte("11010"),
        []byte("11000"),
        []byte("00000"),
    }
    res := numIslands(input)
	fmt.Print(res)
}
