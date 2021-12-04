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


def get_scores(draws, boards):
    scores = []

    for draw in draws:
        i = 0
        while i < len(boards):
            boards[i][boards[i] == draw] = -1
            if np.sum(np.equal(boards[i], -1).all(axis=1)) or np.sum(np.equal(boards[i], -1).all(axis=0)):
                scores.append(np.sum(boards[i][boards[i] != -1]) * draw)
                boards = np.delete(boards, i, axis=0)
                i -= 1
            i += 1
    
    return scores


def main():
    draws, boards = parse('input.txt')

    scores = get_scores(draws, boards)

    print(f'Part 1: {scores[0]}')
    print(f'Part 2: {scores[-1]}')


if __name__ == '__main__':
    main()
