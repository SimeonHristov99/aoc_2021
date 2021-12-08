#include <iostream>
#include <fstream>

#if 0
const char *filename = "sample.txt";
#else
const char *filename = "input.txt";
#endif

const int BUFFER_SZ = 100;
const int NUMBERS_SZ = 4;

void part1()
{
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << filename << '\n';
        return;
    }

    char *buffer = new char[BUFFER_SZ];
    char *buffer_start = buffer;
    int numbers[NUMBERS_SZ];
    int result = 0;

    while (fin.getline(buffer, BUFFER_SZ))
    {
        while (*buffer != '|')
        {
            ++buffer;
        }
        ++buffer;

        do
        {
            ++buffer;

            char *start = buffer;
            while (*buffer && isalpha(*buffer))
            {
                ++buffer;
            }

            if (buffer - start == 2 || buffer - start == 3 || buffer - start == 4 || buffer - start == 7)
            {
                ++result;
            }
        } while (*buffer);

        buffer = buffer_start;
    }

    fin.close();
    delete[] buffer_start;
    buffer_start = nullptr;

    std::cout << "Part 1: " << result << '\n';
}

int main()
{
    part1();

    return 0;
}
