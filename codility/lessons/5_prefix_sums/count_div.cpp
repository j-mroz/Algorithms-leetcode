int solution(int a, int b, int k) {
    int first = (a % k == 0) ? a : (a/k + 1) * k;
    int last = b / k * k;
    return 1 + (last - first) / k;
}
