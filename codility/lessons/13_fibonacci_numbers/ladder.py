_fibs = dict()
_fibs[0] = 0
_fibs[1] = 1
last = 1
max_mod = 2 ** 30

def fib(n, mod):
    global last

    if n not in _fibs:
        f1, f2 = _fibs[last-1], _fibs[last]
        for i in range(last-1, n):
            f1, f2 = f2, (f1 + f2) % max_mod
            _fibs[i+1] = f1

    last = max(last, n)

    return _fibs[n] % mod

def solution(A, B):
   results = []

   for a, b in zip(A, B):
       results.append(fib(a+1, 2**b))

   return results
