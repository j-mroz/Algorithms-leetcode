

def solution(A):

    p, n = 0, len(A)
    triangles_count = 0

    A.sort()

    while p < n - 2:
        q, r = p+1, p+2
        while q < n-1:
            while r < n and A[p] + A[q] > A[r]:
                r += 1
            q += 1
            triangles_count += r - q
        p += 1

    return triangles_count
