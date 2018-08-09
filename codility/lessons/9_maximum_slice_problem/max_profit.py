# https://app.codility.com/programmers/lessons/9-maximum_slice_problem/max_profit/

def solution(A):
    daily_profit = [0] * len(A)

    for i in range(1, len(A)):
        daily_profit[i] = A[i] - A[i-1]

    profit_sum, max_profit = 0, 0
    for profit in daily_profit:
        profit_sum = max(0, profit_sum + profit)
        max_profit = max(max_profit, profit_sum)

    return max_profit
