def part1(moves):
    h_pos = 0
    depth = 0

    for direction, unit in moves:
        if direction == 'forward':
            h_pos += int(unit)
        elif direction == 'up':
            depth -= int(unit)
        elif direction == 'down':
            depth += int(unit)

    return h_pos * depth


def part2(moves):
    aim = 0
    h_pos = 0
    depth = 0

    for direction, unit in moves:
        if direction == 'forward':
            h_pos += unit
            depth += aim * unit
        elif direction == 'up':
            aim -= unit
        elif direction == 'down':
            aim += unit

    return h_pos * depth


def main():
    # Read in the data.
    with open('./day2/input.txt', 'r') as f:
        moves = f.read().split('\n')

    # Ignore this final newline in the input. Frustrating.
    if not moves[-1]:
        moves = moves[:-1]

    # Parse the data in the form (direction, unit).
    parsed_moves = [
        (move.split(' ')[0], int(move.split(' ')[1]))
        for move in moves
    ]

    print(part1(parsed_moves))
    print(part2(parsed_moves))


if __name__ == '__main__':
    main()
