#include <iostream>
#include <fstream>

#if 0
const char *filename = "sample.txt";
#else
const char *filename = "input.txt";
#endif

int parse(int use_aim)
{
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open file!\n";
        return -1;
    }

    int h_pos = 0, depth = 0, aim = 0;

    int units;
    std::string direction;

    while (fin >> direction >> units)
    {
        if (direction == "forward")
        {
            h_pos += units;
            if (use_aim)
            {
                depth += aim * units;
            }
        }
        else if (direction == "up")
        {
            if (use_aim)
            {
                aim -= units;
            }
            else
            {
                depth -= units;
            }
        }
        else if (direction == "down")
        {
            if (use_aim)
            {
                aim += units;
            }
            else
            {
                depth += units;
            }
        }
        else
        {
            std::cout << "Unreachable direction: " << direction << "!\n";
            return -1;
        }
    }

    return h_pos * depth;
}

int part1()
{
    return parse(false);
}

int part2()
{
    return parse(true);
}

int main()
{
    std::cout << "Part 1: " << part1() << '\n';
    std::cout << "Part 2: " << part2() << '\n';

    return 0;
}
