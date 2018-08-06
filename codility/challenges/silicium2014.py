from bisect import bisect_left, bisect_right

class ProductMatrixRow:
	def __init__(self, A, B, y):
		self.A = A
		self.B = B
		self.y = y
	def __getitem__(self, k):
		return self.A[k] * self.B[self.y]
	def __len__(self):
		return len(self.A)

def solution(X, Y, K, A, B):
	A = sorted(a-prev for prev, a in zip([0] + A, A + [X]))
	B = sorted(b-prev for prev, b in zip([0] + B, B + [Y]))
	N = len(A)

	low = A[0]*B[0]
	high = A[-1]*B[-1]

	while low <= high:
		mid = (low + high)/2
		left = bisect_left(ProductMatrixRow(B, A, 0), mid)
		right = bisect_right(ProductMatrixRow(B, A, 0), mid)

		# Find greater or equal split
		y = left
		bigereq = N-y if y < N else 0
		for x in xrange(1, N):
			while y-1 >= 0 and A[x]*B[y-1] >= mid:
				y -= 1
			bigereq += N - y

		# Find "greater tham" split
		y = right
		bigger = N-y if y < len(B) else 0
		for x in xrange(1, N):
			while y-1 >= 0 and A[x]*B[y-1] > mid:
				y -= 1
			bigger += N - y

		# calculate number of elements eqal to mid
		equal = bigereq - bigger

		if equal >= 1 and bigereq-equal < K and K <= bigereq:
			break
		if bigereq >= K:
			low = mid+1
		else:
			high = mid-1

	return mid
