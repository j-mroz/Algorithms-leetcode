package main

import "fmt"

type DisjointSet struct {
    id      []int
    count   int
}

func NewDisjointSet(size int) *DisjointSet {
    this := new(DisjointSet)
    this.id = make([]int, size)
    this.count = size

    for i := range this.id {
        this.id[i] = i
    }

    return this
}

func (this *DisjointSet) Find(idx int) int {
    // Find root element of idx.
    root := idx
    for parent := this.id[root]; root != parent; parent = this.id[root] {
        root = parent
    }

    // Compress path.
    for element := idx; element != root; {
        parent := this.id[element]
        this.id[element] = root
        element = parent
    }

    return root;
}


func (this *DisjointSet) Connect(a, b int) {
    a, b = this.Find(a), this.Find(b)
    if a != b {
        this.id[b] = this.id[a]

        this.count--
    }
}

func (this *DisjointSet) AreConnected(a, b int) bool {
    return this.Find(a) == this.Find(b)
}


func solve(grid [][]byte) {
    if len(grid) == 0 || len(grid[0]) == 0 {
        return
    }

    set := NewDisjointSet(len(grid) * len(grid[0]) + 1)
    start := len(set.id) - 1


    m, n := len(grid), len(grid[0])
    for i, _ := range grid {
        for j, _ := range grid[i] {
            if (i == 0 || i == m-1 || j == 0 || j == n-1) && grid[i][j] == 'O' {
                set.Connect(i * n + j, start)
            }
            if (i > 0 && grid[i][j] == 'O' && grid[i-1][j] == 'O') {
                set.Connect(i * n + j, (i-1) * n + j)
            }
            if (j > 0 && grid[i][j] == 'O' && grid[i][j-1] == 'O') {
                set.Connect(i * n + j, i * n + j - 1)
            }
        }
    }
    for i, _ := range grid {
        for j, _ := range grid[i] {
            if grid[i][j] == 'O' && !set.AreConnected(i * n + j, start) {
                grid[i][j] = 'X'
            }
        }
    }
}

func main() {
    input := [][]byte{
        []byte("OXXOX"),
        []byte("XOOXO"),
        []byte("XOXOX"),
        []byte("OXOOO"),
        []byte("XXOXO"),
    }
    solve(input)
    fmt.Print(input)

}
