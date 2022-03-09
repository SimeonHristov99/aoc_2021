#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cmath>

#if 1
const char *FILENAME = "sample.txt";
const int GRID_CAP = 12;
#else
const char *FILENAME = "input.txt";
const int GRID_CAP = 128;
#endif

struct Cell
{
    int back_i;
    int back_j;
    int i;
    int j;
    int gn = 10000;
    int risk;
};

std::pair<int, int> NEIGHBOURS[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void parse(Cell grid[][GRID_CAP], int &grid_sz)
{
    int i = 0, j = 0;
    std::string buffer;
    std::ifstream fin(FILENAME);

    if (!fin)
    {
        std::cout << "ERROR: Could not open " << FILENAME << '\n';
        return;
    }

    while (std::getline(fin, buffer))
    {
        for (const char c : buffer)
        {
            Cell cell;
            cell.i = -1;
            cell.j = -1;
            cell.back_i = -1;
            cell.back_j = -1;
            cell.risk = c - '0';

            grid[i][j++] = cell;
        }

        ++i;
        j = 0;
    }

    fin.close();

    grid_sz = i;
}

void dump_grid(Cell grid[][GRID_CAP], int grid_sz)
{
    for (int i = 0; i < grid_sz; ++i)
    {
        for (int j = 0; j < grid_sz; ++j)
        {
            std::cout << grid[i][j].j << ' ';
        }
        std::cout << '\n';
    }
}

void dijkstra(Cell grid[][GRID_CAP], int grid_sz)
{
    auto cmp = [](const Cell &c1, const Cell &c2)
    {
        return c1.gn > c2.gn;
    };

    int goal_x = grid_sz - 1;
    int goal_y = grid_sz - 1;
    std::priority_queue<Cell, std::vector<Cell>, decltype(cmp)> frontier(cmp);
    grid[0][0].i = 0;
    grid[0][0].j = 0;
    grid[0][0].back_i = 0;
    grid[0][0].back_j = 0;
    grid[0][0].gn = 0;
    grid[0][0].risk = 0;
    frontier.push(grid[0][0]);

    while (!frontier.empty())
    {
        Cell current_cell = frontier.top();
        frontier.pop();

        // std::cout << current_cell.gn << '\n';

        if (current_cell.i == goal_x && current_cell.j == goal_y)
        {
            std::cout << current_cell.gn << '\n';
            return;
        }

        for (const std::pair<int, int> &neigh : NEIGHBOURS)
        {
            int next_i = current_cell.i + neigh.first;
            int next_j = current_cell.j + neigh.second;

            if (next_i < 0 || next_i >= grid_sz || next_j < 0 || next_j >= grid_sz)
            {
                continue;
            }

            Cell next = grid[next_i][next_j];

            if (next.back_i == -1 && next.back_j == -1 || current_cell.gn + next.risk < next.gn)
            {
                next.back_i = current_cell.i;
                next.back_j = current_cell.j;
                next.i = next_i;
                next.j = next_j;
                next.gn = current_cell.gn + next.risk;
                frontier.push(next);
            }
        }
    }

    std::cout << "Frontier empty :(\n";
}

void part1()
{
    // parse the grid
    int grid_sz = 0;
    Cell grid[GRID_CAP][GRID_CAP];
    parse(grid, grid_sz);
    // dump_grid(grid, grid_sz);

    dijkstra(grid, grid_sz);
}

int main(int argc, char const *argv[])
{
    part1();

    return 0;
}
