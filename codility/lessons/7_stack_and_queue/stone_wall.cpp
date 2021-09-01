#include <stack>
#include <vector>
using namespace std;

int solution(vector<int> &heights) {
    int blocks_used = 0;
    stack<int> blocks;

    for (int h : heights) {
        while (!blocks.empty() && blocks.top() > h) {
            blocks.pop();
        }
        if (blocks.empty() || h > blocks.top()) {
            blocks_used++;
            blocks.push(h);
        }
    }

    return blocks_used;
}
