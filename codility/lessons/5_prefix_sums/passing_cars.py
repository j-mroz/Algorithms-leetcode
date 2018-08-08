# https://app.codility.com/programmers/lessons/5-prefix_sums/passing_cars/

class PrefixSumArray:

    def __init__(self, values):
        self.arr = [0] * (len(values) + 1)
        for (i, value) in enumerate(values):
            self.arr[i+1] = self.arr[i] + value

    def query_range(self, first, last):
        return self.arr[last+1] - self.arr[first]



def solution(A):
    east_direction, cars_traveling_west = 0,  PrefixSumArray(A)
    passing_cars, last_car = 0, len(A)-1

    for (car_pos, direction) in enumerate(A):
        if direction == east_direction:
            passing_cars += cars_traveling_west.query_range(car_pos+1, last_car)
        if passing_cars > 1_000_000_000:
            return -1

    return passing_cars
