# https://app.codility.com/programmers/lessons/6-sorting/max_product_of_three/

def solution(A):
   A.sort()
   return max(A[-1]*A[-2]*A[-3], A[0]*A[1] * A[-1])
