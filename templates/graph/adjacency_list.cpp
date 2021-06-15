#include <iostream>
#include <vector>
#include <list>
#include <queue>

using std::vector;
using std::list;
using std::queue;

/**
 * Optional template parameter
 */
struct Optional {
};

/**
 * Tuple, up to thre elements only
 */
template <typename First, typename Second, typename Third  = Optional>
struct Tuple {
    First first;
    Second second;
    Third third;
};
template <typename First, typename Second>
struct Tuple<First, Second, Optional> {
    int first;
    int second;
};

/**
 * Edge representation
 */
template <typename Data = Optional>
struct StoredEdge {

    StoredEdge(int source, int adjacent) { 
        this->source() = source;
        this->adjacent() = adjacent;
    }

    StoredEdge(int source, int adjacent, Data data) { 
        this->source() = source;
        this->adjacent() = adjacent;
        this->data() = data;
    }

    inline int& source() {
        return self.first;
    }

    inline int& adjacent() {
        return self.second;
    }

    inline Data& data() {
        return self.third;
    }

    Tuple<int, int, Data> self;
};





/**
 * Vertex representation
 */
// struct StoredVertex {
//     list<Edge> edges;
// };
// typedef list<Edge>::iterator EdgeIterator;

/**
 * Adjacency list
 */
template<typename VertexData = std::size_t, typename EdgeData = Optional>
class AdjacencyList {
public:
    typedef ::StoredEdge<EdgeData> StoredEdge;
    typedef list<StoredEdge> EdgeList;

    vector<EdgeList> vertices_edges_;
    vector<VertexData> vertices_;

public:
    std::size_t AddVertex(const VertexData& data) {
        vertices_.push_back(data);
        vertices_edges_.push_back( EdgeList() );
        return vertices_.size()-1;
    }
    void AddEdge(std::size_t u, std::size_t v) {
        AdjacencyListOf(u).push_back( MakeEdge(u, v) );
    }
    void AddEdge(std::size_t u, std::size_t v, const EdgeData& data) {
        AdjacencyListOf(u).push_back( MakeEdge(u, v, data) );
    }
    inline EdgeList& AdjacencyListOf(std::size_t u) {
        return vertices_edges_.at(u); // Safty
        // return vertices_edges_[u]; // Performance
    }
    inline StoredEdge MakeEdge(std::size_t u, std::size_t v) {
        return StoredEdge(u, v);
    }
    inline StoredEdge MakeEdge(std::size_t u, std::size_t v, const EdgeData& data) {
        return StoredEdge(u, v, data);
    }
};



int main() {
    
    typedef AdjacencyList<int> Graph;
    Graph graph;
    std::size_t u = graph.AddVertex(8);;
    std::size_t v = graph.AddVertex(1);

    graph.AddEdge(u, v);
    graph.AddEdge(555, 15);

    return 0;
}