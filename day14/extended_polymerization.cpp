#include <iostream>
#include <fstream>
#include <vector>

const char *FILENAME = "sample.txt";
const int SIZE = 26;
const int STEPS = 1;

void parse(std::vector<std::string> &subs, int grid[][SIZE][2])
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
        ++grid[buffer[i] - 'A'][buffer[i + 1] - 'A'][0];
        grid[buffer[i] - 'A'][buffer[i + 1] - 'A'][1] = true;
    }

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

void init_grid(int grid[][SIZE][2])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            grid[i][j][0] = 0;
            grid[i][j][1] = 0;
        }
    }
}

void print_grid(int grid[][SIZE][2])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            std::cout << '[' << grid[i][j][0] << ' ' << grid[i][j][1] << "] ";
        }
        std::cout << '\n';
    }
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> subs;
    int grid[SIZE][SIZE][2];

    init_grid(grid);
    parse(subs, grid);

    for (int step = 0; step < STEPS; ++step)
    {
        for (const std::string &sub : subs)
        {
            if (grid[sub[0] - 'A'][sub[1] - 'A'][1])
            {
                std::cout << "match for " << sub[0] << sub[1] << '\n';
                grid[sub[0] - 'A'][sub[1] - 'A'][1] = false;

                ++grid[sub[0] - 'A'][sub[2] - 'A'][0];
                grid[sub[0] - 'A'][sub[2] - 'A'][1] = true;
            }
        }
    }

    print_grid(grid);

    return 0;
}