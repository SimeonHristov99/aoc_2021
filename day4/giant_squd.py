import numpy as np


def parse(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()

    draws = list(map(int, lines[0].rstrip().split(',')))

    boards = []
    board = []

    for line in lines[1:]:
        if line.strip():
            board.append(list(map(int, line.strip().split())))
        elif len(board) > 1:
            boards.append(board)
            board = []

    boards.append(board)

    return draws, np.array(boards)


def part1(draws, boards):
    for draw in draws:
        for board in boards:
            board[board == draw] = -1
            if np.sum(np.equal(board, -1).all(axis=1)) or np.sum(np.equal(board, -1).all(axis=0)):
                return np.sum(board[board != -1]) * draw


def main():
    draws, boards = parse('input.txt')

    print(f'Part 1: {part1(draws, boards)}')


if __name__ == '__main__':
    main()
