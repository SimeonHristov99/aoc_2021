#include <iostream>
#include <fstream>
#include <vector>

const int SIZE = 26;

#if 0
const char *FILENAME = "sample.txt";
#else
const char *FILENAME = "input.txt";
#endif

void init_grid(long grid[][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            grid[i][j] = 0;
        }
    }
}

void init_grid(long grid[][SIZE], long rhs[][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            grid[i][j] = rhs[i][j];
        }
    }
}

void parse(
    std::vector<std::string> &subs,
    long grid[][SIZE],
    long occurs[SIZE])
{
    std::string buffer, sub;
    std::ifstream fin(FILENAME);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << FILENAME << '\n';
        fin.close();
        return;
    }

    std::getline(fin, buffer);

    int len_buf = buffer.length();
    for (int i = 0; i < len_buf - 1; i++)
    {
        int from = buffer[i] - 'A';
        int to = buffer[i + 1] - 'A';

        ++grid[from][to];

        ++occurs[from];
    }
    ++occurs[buffer[len_buf - 1] - 'A'];

    std::getline(fin, buffer);

    while (std::getline(fin, buffer))
    {
        sub += buffer[0];
        sub += buffer[1];
        sub += buffer[6];

        subs.push_back(sub);
        sub = "";
    }

    fin.close();
}

long breed(int steps)
{
    std::vector<std::string> subs;
    long occurs[SIZE] = {0};
    long prev_grid[SIZE][SIZE];
    long cur_grid[SIZE][SIZE];

    init_grid(prev_grid);
    parse(subs, prev_grid, occurs);
    init_grid(cur_grid, prev_grid);

    for (int step = 0; step < steps; ++step)
    {
        // consider all pairs "simultaneously"
        for (const std::string &sub : subs)
        {
            if (prev_grid[sub[0] - 'A'][sub[1] - 'A'] <= 0)
            {
                continue;
            }

            // insert new letter
            // NN, A
            // NAN
            cur_grid[sub[0] - 'A'][sub[2] - 'A'] += prev_grid[sub[0] - 'A'][sub[1] - 'A'];
            cur_grid[sub[2] - 'A'][sub[1] - 'A'] += prev_grid[sub[0] - 'A'][sub[1] - 'A'];

            // increment the occurences of the new element
            occurs[sub[2] - 'A'] += prev_grid[sub[0] - 'A'][sub[1] - 'A'];

            // disconnect pair
            cur_grid[sub[0] - 'A'][sub[1] - 'A'] -= prev_grid[sub[0] - 'A'][sub[1] - 'A'];
        }

        init_grid(prev_grid, cur_grid);
    }

    long max = 0;

    for (int i = 1; i < SIZE; ++i)
    {
        if (0 < occurs[i] && max < occurs[i])
        {
            max = occurs[i];
        }
    }

    long min = max;

    for (int i = 1; i < SIZE; ++i)
    {
        if (0 < occurs[i] && occurs[i] < min)
        {
            min = occurs[i];
        }
    }

    return max - min;
}

int main(int argc, char const *argv[])
{
    std::cout << "Part 1: " << breed(10) << '\n';
    std::cout << "Part 2: " << breed(40) << '\n';

    return 0;
}