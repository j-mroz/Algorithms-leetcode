#include <stack>
#include <vector>
using namespace std;

enum class Direction : int {Downstream = 1, Upstream = 0};

int solution(vector<int> &ranks, vector<int> &directions) {
    int alive = 0;
    stack<int> downstream_ranks;

    for (size_t i = 0; i < ranks.size(); i++) {
        if (static_cast<Direction>(directions[i]) == Direction::Downstream) {
            downstream_ranks.push(ranks[i]);
            alive++;
        }
        if (static_cast<Direction>(directions[i]) == Direction::Upstream) {
            while (!downstream_ranks.empty() && downstream_ranks.top() < ranks[i]) {
                downstream_ranks.pop();
                alive--;
            }
            if (downstream_ranks.empty()) {
                alive++;
            }
        }
    }

    return alive;
}
