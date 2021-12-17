#include <iostream>
#include <fstream>
#include <vector>

#if 0
const char *filename = "sample.txt";
const int FOLDS_CAP = 2;
#else
const char *filename = "input.txt";
const int FOLDS_CAP = 12;
#endif

const int GRID_CAP = 2048;

std::string split_by_delim(const std::string &s, const char delim, std::string &out)
{
    std::string rest;

    int len_s = s.length();
    int i = 0;
    while (i < len_s && s[i] != delim)
    {
        out += s[i++];
    }

    ++i;

    while (i < len_s)
    {
        rest += s[i++];
    }

    return rest;
}

void dump_folds(int folds[FOLDS_CAP][2])
{
    for (int i = 0; i < FOLDS_CAP; ++i)
    {
        std::cout << '(' << (folds[i][0] == 1 ? 'x' : 'y') << ' ' << folds[i][1] << ") ";
    }
    std::cout << '\n';
}

void parse(char grid[GRID_CAP][GRID_CAP], int folds[][2])
{
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << filename << '\n';
        return;
    }

    std::string buffer;

    while (std::getline(fin, buffer) && buffer != "")
    {
        std::string x;
        std::string y = split_by_delim(buffer, ',', x);

        int num_x = atoi(x.c_str());
        int num_y = atoi(y.c_str());

        grid[num_y][num_x] = '#';
    }

    int i = 0;
    while (std::getline(fin, buffer))
    {
        std::string x;
        std::string y = split_by_delim(buffer, '=', x);

        folds[i][0] = (x[x.length() - 1] == 'x' ? 1 : 0);
        folds[i++][1] = atoi(y.c_str());
    }

    fin.close();
}

void init_with(char grid[GRID_CAP][GRID_CAP], const char c)
{
    for (int i = 0; i < GRID_CAP; ++i)
    {
        for (int j = 0; j < GRID_CAP; ++j)
        {
            grid[i][j] = c;
        }
    }
}

void dump_grid(char grid[GRID_CAP][GRID_CAP], const size_t rows, const size_t cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << grid[i][j];
        }
        std::cout << '\n';
    }
}

void fold_y(char grid[GRID_CAP][GRID_CAP], size_t &rows, const size_t cols, const int y)
{
    for (int i = 0; i < y; ++i)
    {
        for (int j = 0; j < GRID_CAP; ++j)
        {
            grid[i][j] = (grid[i][j] == '#' || grid[rows - 1 - i][j] == '#' ? '#' : '.');
        }
    }

    rows -= y + 1;
}

void fold_x(char grid[GRID_CAP][GRID_CAP], const size_t rows, size_t &cols, const int x)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < x; ++j)
        {
            grid[i][j] = (grid[i][j] == '#' || grid[i][cols - 1 - j] == '#' ? '#' : '.');
        }
    }

    cols -= x + 1;
}

int count_hashes(char grid[GRID_CAP][GRID_CAP], const size_t rows, const size_t cols)
{
    int result = 0;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (grid[i][j] == '#')
            {
                ++result;
            }
        }
    }

    return result;
}

void part1()
{
    int folds[FOLDS_CAP][2];
    char grid[GRID_CAP][GRID_CAP];

    init_with(grid, '.');

    parse(grid, folds);

    size_t rows = 0, cols = 0;

    if (folds[0][0] == 1)
    {
        rows = folds[1][1] * 2 + 1;
        cols = folds[0][1] * 2 + 1;

        fold_x(grid, rows, cols, folds[0][1]);
    }
    else
    {
        rows = folds[0][1] * 2 + 1;
        cols = folds[1][1] * 2 + 1;

        fold_y(grid, rows, cols, folds[0][1]);
    }

    std::cout << "Part 1: " << count_hashes(grid, rows, cols) << '\n';
}

void part2()
{
    int folds[FOLDS_CAP][2];
    char grid[GRID_CAP][GRID_CAP];

    init_with(grid, '.');

    parse(grid, folds);

    size_t rows = 0, cols = 0;

    if (folds[0][0] == 1)
    {
        rows = folds[1][1] * 2 + 1;
        cols = folds[0][1] * 2 + 1;
    }
    else
    {
        rows = folds[0][1] * 2 + 1;
        cols = folds[1][1] * 2 + 1;
    }

    for (int i = 0; i < FOLDS_CAP; ++i)
    {
        if (folds[i][0] == 1)
        {
            fold_x(grid, rows, cols, folds[i][1]);
        }
        else
        {
            fold_y(grid, rows, cols, folds[i][1]);
        }
    }

    std::cout << "Part 2:\n";
    dump_grid(grid, rows, cols);
}

int main(int argc, char const *argv[])
{
    part1();
    part2();

    return 0;
}
