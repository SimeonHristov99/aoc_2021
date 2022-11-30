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


def part1(file: str):
    cave = np.genfromtxt(file, delimiter=1, dtype=int)

    print(cave)
    print(f'{cave.shape=}')

    end_x = cave.shape[0] - 1
    end_y = cave.shape[1] - 1

    print('Searching ...')
    res = bfs(cave, (0, 0), (end_x, end_y))
    print(res.total_risk)


def part2(file: str):
    cave0 = np.genfromtxt(file, delimiter=1, dtype=int)

    caves = np.tile(cave0, (5, 5, 1)).reshape(5, 5, *cave0.shape)
    # print(caves[0, 0])
    
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

    end_x = caves.shape[0] - 1
    end_y = caves.shape[1] - 1

    print('Searching ...')
    res = bfs(caves, (0, 0), (end_x, end_y))
    print(res.total_risk)


def main():
    # part1('./sample.txt')
    # part1('./input.txt')

    # part2('./sample.txt')
    part2('./input.txt')


if __name__ == '__main__':
    main()
