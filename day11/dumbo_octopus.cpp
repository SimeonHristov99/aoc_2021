#include <iostream>
#include <fstream>
#include <cassert>
#include <stack>
#include <set>

#if 0
const char *filename = "sample.txt";
#else
const char *filename = "input.txt";
#endif

const int GRID_SIZE = 10;
const int STEPS = 100;

void parse_grid(int grid[][GRID_SIZE])
{
    std::ifstream fin(filename);
    if (!fin)
    {
        printf("ERROR: Could not open %s\n", filename);
        return;
    }

    std::string buffer;

    int i = 0, j = 0;
    while (std::getline(fin, buffer))
    {
        for (const char c : buffer)
        {
            grid[i][j++] = c - '0';
        }
        ++i;
        j = 0;
    }

    fin.close();

    assert(i == GRID_SIZE);
}

void dump_grid(int grid[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            std::cout << grid[i][j];
        }
        std::cout << '\n';
    }
}

void step(int grid[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            ++grid[i][j];
        }
    }
}

int flash(int grid[][GRID_SIZE])
{
    int result = 0;

    std::stack<std::pair<int, int>> frontier;
    std::set<std::pair<int, int>> visited;

    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            if (grid[i][j] == 10)
            {
                frontier.push({i, j});
            }
        }
    }

    while (!frontier.empty())
    {
        std::pair<int, int> top = frontier.top();
        frontier.pop();

        grid[top.first][top.second] = 0;
        ++result;
        visited.insert(top);

        for (int i = top.first - 1; i < top.first + 2; ++i)
        {
            for (int j = top.second - 1; j < top.second + 2; ++j)
            {
                if (
                    i == top.first && j == top.second
                    || i < 0 || j < 0
                    || i >= GRID_SIZE || j >= GRID_SIZE
                    || visited.find({i, j}) != visited.end()
                )
                    continue;

                ++grid[i][j];
                if (grid[i][j] == 10)
                {
                    frontier.push({i, j});
                }
            }
        }
    }

    return result;
}

void part1()
{
    int result = 0;
    int grid[GRID_SIZE][GRID_SIZE];

    parse_grid(grid);

    for (int i = 0; i < STEPS; ++i)
    {
        step(grid);

        result += flash(grid);
    }

    printf("Part 1: %d\n", result);
}

void part2()
{
    int grid[GRID_SIZE][GRID_SIZE];

    parse_grid(grid);

    int i = 0;
    for (; flash(grid) != GRID_SIZE * GRID_SIZE; ++i)
    {
        step(grid);
    }

    printf("Part 2: %d\n", i);
}

int main(int argc, char const *argv[])
{
    part1();
    part2();

    return 0;
}
