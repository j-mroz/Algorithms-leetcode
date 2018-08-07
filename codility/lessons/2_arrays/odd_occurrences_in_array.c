// https://app.codility.com/programmers/lessons/2-arrays/odd_occurrences_in_array/

int solution(int A[], int N) {
    int number = 0;
    for (int i = 0; i < N; i++) {
        number ^= A[i];
    }
    return number;
}
