import numpy as np
from queue import PriorityQueue
import functools


@functools.total_ordering
class Node:
    def __init__(self, x, y, total_risk):
        self.x = x
        self.y = y
        self.total_risk = total_risk

    def __lt__(self, other):
        return self.total_risk < other.total_risk

    def __eq__(self, other):
        return self.total_risk == other.total_risk


def is_valid(coord, upper_limit):
    return 0 <= coord[0] < upper_limit and 0 <= coord[1] < upper_limit


def bfs(matrix, start, end):
    q = PriorityQueue()
    q.put(Node(start[0], start[1], 0))
    visited = set()
    upper_limit = matrix.shape[0]

    while not q.empty():
        current_node = q.get()
        x, y, tot_risk = current_node.x, current_node.y, current_node.total_risk
        visited.add((x, y))

        if (x, y) == end:
            return current_node

        candid = (x-1, y)
        if candid not in visited and is_valid(candid, upper_limit):
            # left
            q.put(Node(*candid, tot_risk + matrix[candid]))
            visited.add((x, y))

        candid = (x, y-1)
        if candid not in visited and is_valid(candid, upper_limit):
            # up
            q.put(Node(*candid, tot_risk + matrix[candid]))
            visited.add((x, y))

        candid = (x+1, y)
        if candid not in visited and is_valid(candid, upper_limit):
            # right
            q.put(Node(*candid, tot_risk + matrix[candid]))
            visited.add((x, y))

        candid = (x, y+1)
        if candid not in visited and is_valid(candid, upper_limit):
            # down
            q.put(Node(*candid, tot_risk + matrix[candid]))
            visited.add((x, y))

    return -1


def dp(matrix):
    table = np.zeros_like(matrix)

    size = matrix.shape[0]

    for j in range(1, size):
        table[0, j] = table[0, j - 1] + matrix[0, j]

    for i in range(1, size):
        table[i, 0] = table[i - 1, 0] + matrix[i, 0]

    for i in range(1, size):
        for j in range(1, size):
            table[i, j] = min(table[i - 1, j], table[i, j - 1]) + matrix[i, j]

    print(table)

    return table[size - 1, size - 1]


def part1(file: str):
    cave = np.genfromtxt(file, delimiter=1, dtype=int)
    return dp(cave)


def part2(file: str):
    cave0 = np.genfromtxt(file, delimiter=1, dtype=int)

    caves = np.tile(cave0, (5, 5, 1)).reshape(5, 5, *cave0.shape)

    for i in range(5):
        for j in range(5):
            if i == 0 and j == 0:
                continue

            if i == 0:
                caves[i, j] = caves[i, j - 1] + 1
            else:
                caves[i, j] = caves[i - 1, j] + 1

            caves[i, j] = np.where(caves[i, j] > 9, 1, caves[i, j])

    caves = np.concatenate(caves, -2)
    caves = np.concatenate(caves, -1)

    return dp(caves)


def main():
    # print(f"Part 1 (sample): {part1('./sample.txt')}")
    print(f"Part 1 (input): {part1('./input.txt')}")

    print(f"Part 2 (sample): {part2('./sample.txt')}")
    # print(f"Part 2 (input): {part2('./input.txt')}")


if __name__ == '__main__':
    main()
