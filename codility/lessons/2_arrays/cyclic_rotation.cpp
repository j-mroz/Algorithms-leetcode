// https://app.codility.com/programmers/lessons/2-arrays/cyclic_rotation/

#include <vector>
using namespace std;

vector<int> rotate(const vector<int> &arr, int k) {
    auto size = arr.size();
    auto rotated = vector<int>(size);

    for (size_t index = 0; index < size; index++) {
        size_t shifted_index = (index + k) % size;
        rotated[shifted_index] = arr[index];
    }

    return rotated;
}

vector<int> solution(vector<int> &A, int K) {
    return rotate(A, K);
}
