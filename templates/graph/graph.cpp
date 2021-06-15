#include <vector>
#include <list>
#include <queue>

using std::vector;
using std::list;
using std::queue;

/**
 * Edge representation
 */
struct Edge {
    int source;
    int destination;
};


/**
 * Vertex representation
 */
struct Vertex {
    list<Edge> edges;
};
typedef list<Edge>::iterator EdgeIterator;

/**
 * Graph representation
 */
class Graph {
    vector<Vertex> vertices_;

public:
    explicit Graph(int vertices_count = 0);
    void BroadFirstSearch(int start_vertex);
    void DeepFirstSearch();
    void StronglyConnectedComponentsGraph();
    void TopologicalSort();
    void MinimalSpaningTree();
};

/**
 * Constructor of graph
 */
Graph::Graph(int vertices_count) {
    vertices_.resize(vertices_count+1);
    vertices_[0] = Vertex(); // A guard, not really need as it would be constructed anyway

}

/**
 * BFS
 */
void Graph::BroadFirstSearch(int start_vertex) {

    // Init visit queue
    vector<bool> visited_vertices(vertices_.size(), false);
    queue<int> visit_queue;
    visit_queue.push(start_vertex);

    // Visit nodes
    while (!visit_queue.empty()) {
        // Get vertex from queue head
        int vertex_number = visit_queue.front();
        visit_queue.pop();

        // For each neigbouring edge
        EdgeIterator edge_iterator = vertices_[vertex_number].edges.begin();
        EdgeIterator edges_end = vertices_[vertex_number].edges.end();
        for ( ; edge_iterator != edges_end; ++edge_iterator) {

        }

    }
}

int main() {
    Graph g;
    return 0;
}