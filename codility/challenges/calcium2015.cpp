#include <vector>
using namespace std;

struct CalciumSolver {
    vector<vector<int>> adjList;
    vector<int> treeDepth;
    int edgesToRemove;
    const size_t MaxDistance = 900;

    CalciumSolver(vector<int> &A, vector<int> &B, int K) {
        createAdjList(A, B);
        edgesToRemove = K;
    }

    void createAdjList(vector<int> &A, vector<int> &B) {
        int graphSize = A.size()+1;
        adjList.resize(graphSize);
        treeDepth.resize(graphSize);
        for (int idx = 0; idx < A.size(); ++idx) {
            int u = A[idx], v = B[idx];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
    }

    int countSplitablePaths(int root, int maxPath) {
        return countSplitablePathsVisit(-1, root, maxPath);
    }

    int countSplitablePathsVisit(int parent, int vertex, int maxPath) {
        int result = 0;
        treeDepth[vertex] = 0;

        for (int child : adjList[vertex]) {
            if (child == parent)
                continue;
            result += countSplitablePathsVisit(vertex, child, maxPath);
            if (treeDepth[child] + 1 + treeDepth[vertex] > maxPath) {
                treeDepth[vertex] = min(treeDepth[vertex], treeDepth[child] + 1);
                result++;
            }
            else {
                treeDepth[vertex] = max(treeDepth[vertex], treeDepth[child] + 1);
            }
        }

        return result;
    }


    int run() {
        int result = -1;
        int begin = 0;
        int end = min(MaxDistance, adjList.size());

        // inclusive bisection
        while (begin < end) {
            int mid = begin + (end - begin)/2;
            int removableEdges = countSplitablePaths(0, mid);
            if (edgesToRemove >= removableEdges)
                result = end = mid;
            else
                begin = mid + 1;
        }
        return result;
    }
};

int solution(vector<int> &A, vector<int> &B, int K) {
    CalciumSolver solver(A, B, K);
    return solver.run();
}
