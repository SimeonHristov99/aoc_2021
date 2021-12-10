#include <iostream>
#include <fstream>

#if 0
const char *filename = "sample.txt";
const int POS_SZ = 12;
#else
const char *filename = "input.txt";
const int POS_SZ = 4096;
#endif

void parse_numbers(const std::string &input, int *result, size_t &size)
{
    std::string number;

    for (const char c : input)
    {
        if (c == ',')
        {
            result[size++] = atoi(number.c_str());
            number = "";
        }
        else
        {
            number += c;
        }
    }
    result[size++] = atoi(number.c_str());
}

void part1()
{
    int positions[POS_SZ] = {0};
    size_t pos_size = 0;

    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << filename << '\n';
        return;
    }

    std::string buffer;
    std::getline(fin, buffer);

    parse_numbers(buffer, positions, pos_size);

    int min_score = -1;

    for (int position = 0; position < pos_size; ++position)
    {
        int current_score = 0;

        for (int i = 0; i < pos_size; ++i)
        {
            current_score += abs(positions[i] - position);
        }

        if (min_score < 0 || current_score < min_score)
        {
            min_score = current_score;
        }
    }

    std::cout << "Part 1: " << min_score << '\n';
}
void part2()
{
    int positions[POS_SZ] = {0};
    size_t pos_size = 0;

    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << filename << '\n';
        return;
    }

    std::string buffer;
    std::getline(fin, buffer);

    parse_numbers(buffer, positions, pos_size);

    int min_score = -1;

    for (int position = 0; position < pos_size; ++position)
    {
        int current_score = 0;

        for (int i = 0; i < pos_size; ++i)
        {
            int distance = abs(positions[i] - position);
            current_score += distance * (distance + 1) / 2;
        }

        if (min_score < 0 || current_score < min_score)
        {
            min_score = current_score;
        }
    }

    std::cout << "Part 2: " << min_score << '\n';
}


int main(int argc, char const *argv[])
{
    part1();
    part2();

    return 0;
}
