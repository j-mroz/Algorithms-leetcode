# https://app.codility.com/programmers/lessons/6-sorting/number_of_disc_intersections/

START, END = 0, 1

def solution(A):

    start_points = [(center-radious, START) for (center, radious) in enumerate(A)]
    end_points = [(center+radious, END) for (center, radious) in enumerate(A)]
    points = start_points + end_points
    points.sort()

    intersections = 0
    opened_discs = 0

    for (point, point_type) in points:
        if point_type == START:
            opened_discs += 1
        else:
            opened_discs -= 1
            intersections += opened_discs
        if intersections > 10_000_000:
            return -1

    return intersections
