// https://app.codility.com/programmers/lessons/4-counting_elements/missing_integer/


int solution(vector<int> &A) {
    int max_missing = A.size()+1;
    auto counter = vector<int>(max_missing, 0);
    for (int number : A) {
        number--;
        if ((size_t)number < max_missing) {
            counter[number]++;
        }
    }
    for (int number = 0; number < max_missing; number++) {
        if (counter[number] == 0) {
            return number+1;
        }
    }
    return -1;
}
