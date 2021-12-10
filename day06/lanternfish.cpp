#include <iostream>
#include <fstream>

#if 0
const char *filename = "sample.txt";
#else
const char *filename = "input.txt";
#endif

const size_t AGES_SZ = 9;
const size_t DAYS = 256;

void parse_numbers(const std::string &input, long *result)
{
    std::string number;

    for (const char c : input)
    {
        if (c == ',')
        {
            ++result[atoi(number.c_str())];
            number = "";
        }
        else
        {
            number += c;
        }
    }
    ++result[atoi(number.c_str())];
}

long count_ages(const long *ages)
{
    long result = 0;

    for (int i = 0; i < AGES_SZ; ++i)
    {
        result += ages[i];
    }

    return result;
}

long breed(const int epochs)
{
    long ages[AGES_SZ] = {0};

    std::fstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << filename << '\n';
        return -1;
    }

    std::string buffer;
    std::getline(fin, buffer);

    parse_numbers(buffer, ages);

    for (int epoch = 0; epoch < epochs; ++epoch)
    {
        long to_add = ages[0];

        for (int i = 0; i < AGES_SZ - 1; ++i)
        {
            ages[i] = ages[i + 1];
        }

        ages[AGES_SZ - 1] = to_add;
        ages[6] += to_add;
    }

    return count_ages(ages);
}

int main(int argc, char const *argv[])
{
    std::cout << "Part 1: " << breed(80) << '\n';
    std::cout << "Part 2: " << breed(256) << '\n';

    return 0;
}
