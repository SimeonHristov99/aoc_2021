import numpy as np
from queue import Queue

NEIGHBORS = {
    (-1, 0),
    (0, -1),
    (1, 0),
    (0, 1),
}

BIG_SIZE = 5


def part1(file: str):
    q = Queue()

    cave = np.genfromtxt(file, delimiter=1, dtype=int)
    init_s = cave.shape[0]
    size = cave.shape[0]

    table_dists = np.zeros((size, size)) + np.inf
    table_dists[0, 0] = 0

    q.put((0, 0))

    while not q.empty():
        (x, y) = q.get()

        for (dx, dy) in NEIGHBORS:
            i = x + dx
            j = y + dy

            risk = get_big_map_val(
                cave[i % init_s, j % init_s], i // init_s, j // init_s)

            if 0 <= i < size and 0 <= j < size \
                    and table_dists[x, y] + risk < table_dists[i, j]:
                table_dists[i, j] = table_dists[x, y] + risk
                q.put((i, j))

    return table_dists[-1, -1].astype(int)


def get_big_map_val(n, i, j):
    return ((n - 1 + j) % 9 + i) % 9 + 1


def part2(file: str):
    q = Queue()

    cave = np.genfromtxt(file, delimiter=1, dtype=int)
    init_s = cave.shape[0]
    size = cave.shape[0] * BIG_SIZE

    table_dists = np.zeros((size, size)) + np.inf
    table_dists[0, 0] = 0

    q.put((0, 0))

    while not q.empty():
        (x, y) = q.get()

        for (dx, dy) in NEIGHBORS:
            i = x + dx
            j = y + dy

            risk = get_big_map_val(
                cave[i % init_s, j % init_s], i // init_s, j // init_s)

            if 0 <= i < size and 0 <= j < size \
                    and table_dists[x, y] + risk < table_dists[i, j]:
                table_dists[i, j] = table_dists[x, y] + risk
                q.put((i, j))

    return table_dists[-1, -1].astype(int)


def main():
    print(f"Part 1 (sample): {part1('./sample.txt')}")
    print(f"Part 1 (input): {part1('./input.txt')}")
    print()
    print(f"Part 2 (sample): {part2('./sample.txt')}")
    print(f"Part 2 (input): {part2('./input.txt')}")


if __name__ == '__main__':
    main()
