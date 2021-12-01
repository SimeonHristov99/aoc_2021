def times_incresed(distances):
    result = 0

    for i in range(1, len(distances)):
        if distances[i] > distances[i - 1]:
            result += 1

    return result


def part1(distances):
    return times_incresed(distances)


def part2(distances):
    batches = [
        distances[i:i+3]
        for i in range(0, len(distances))
        if len(distances[i:i+3]) == 3
    ]

    l = list(map(sum, batches))

    return times_incresed(l)


def main():
    # Read the input from the file into a list.
    with open('./day1/input.txt', 'r') as f:
        distances = f.read()

    # Parse the input string into a list of numbers.
    # [:-1] for ignoring the final newline
    distances = list(map(int, distances.split('\n')))

    # print(part1(distances))
    print(part2(distances))


if __name__ == '__main__':
    main()
