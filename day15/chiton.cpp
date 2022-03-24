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

const int TIMES_ENLARGE = 5;

struct Step
{
    std::pair<int, int> coords;
    int cost;
};

struct Cell
{
    int risk;
    bool has_step;
    Step step;
};

std::pair<int, int> NEIGHBOURS[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

/*
Idea to try out: Maybe create a table of the values by which the risk has
to increase based on the grid.
The goal is to have 1 grid that can be reused 25 times.

Formula for risk_inc = ((risk_inc + inc_with_table[i][j]) % 10 + 1)
*/

const int TABLE[5][5] = {
    {0, 1, 2, 3, 4},
    {1, 2, 3, 4, 5},
    {2, 3, 4, 5, 6},
    {3, 4, 5, 6, 7},
    {4, 5, 6, 7, 8},
};

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
            cell.risk = c - '0';
            cell.has_step = false;

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
            std::cout << grid[i][j].risk << ' ';
        }
        std::cout << '\n';
    }
}

int ucs_p1(Cell grid[][GRID_CAP], int grid_sz)
{
    auto cmp = [](const Step &s1, const Step &s2)
    {
        return s1.cost > s2.cost;
    };

    int goal_x = grid_sz - 1;
    int goal_y = grid_sz - 1;

    std::priority_queue<Step, std::vector<Step>, decltype(cmp)> frontier(cmp);
    grid[0][0].step = {{0, 0}, 0};
    grid[0][0].has_step = true;
    frontier.push(grid[0][0].step);

    while (!frontier.empty())
    {
        Step last_cell = frontier.top();
        frontier.pop();

        int x, y;
        x = last_cell.coords.first;
        y = last_cell.coords.second;

        if (x == goal_x && y == goal_y)
        {
            break;
        }

        for (const std::pair<int, int> &neigh : NEIGHBOURS)
        {
            int x2 = x + neigh.first;
            int y2 = y + neigh.second;

            if (x2 < 0 || x2 >= grid_sz || y2 < 0 || y2 >= grid_sz)
            {
                continue;
            }

            Cell &next_cell = grid[x2][y2];
            int next_cost = last_cell.cost + next_cell.risk;
            if (!next_cell.has_step || next_cost < next_cell.step.cost)
            {
                next_cell.has_step = true;
                next_cell.step = {{x2, y2}, next_cost};
                frontier.push(next_cell.step);
            }
        }
    }

    return grid[goal_x][goal_y].step.cost;
}

int ucs_p2(Cell grid[][GRID_CAP], const int grid_sz)
{
    auto cmp = [](const Step &s1, const Step &s2)
    {
        return s1.cost > s2.cost;
    };

    std::pair<int, int> tile_coords = {0, 0};
    std::pair<int, int> goal_coords = {grid_sz - 1, grid_sz - 1};
    std::pair<int, int> goal_tile_coords = {TIMES_ENLARGE - 1, TIMES_ENLARGE - 1};
    std::priority_queue<Step, std::vector<Step>, decltype(cmp)> frontier(cmp);

    grid[0][0].step = {{0, 0}, 0};
    grid[0][0].has_step = true;
    frontier.push(grid[0][0].step);

    while (!frontier.empty())
    {
        Step last_cell = frontier.top();
        frontier.pop();

        std::pair<int, int> last_cell_coords = last_cell.coords;

        if (last_cell_coords == goal_coords && tile_coords == goal_tile_coords)
        {
            break;
        }

        for (const std::pair<int, int> &neigh : NEIGHBOURS)
        {
            int x2 = last_cell_coords.first + neigh.first;
            int y2 = last_cell_coords.second + neigh.second;

            if (x2 < 0 && 0 <= y2 && y2 < grid_sz) // new grid above
            {
                if (tile_coords.first <= 0)
                {
                    continue;
                }

                --tile_coords.first;
                x2 = grid_sz - 1;
            }
            else if (y2 < 0 && 0 <= x2 && x2 < grid_sz) // new grid left
            {
                if (tile_coords.second <= 0)
                {
                    continue;
                }

                --tile_coords.second;
                y2 = grid_sz - 1;
            }
            else if (y2 >= grid_sz && 0 <= x2 && x2 < grid_sz) // new grid right
            {
                if (tile_coords.second >= TIMES_ENLARGE - 1)
                {
                    continue;
                }

                ++tile_coords.second;
                y2 = 0;
            }
            else if (x2 >= grid_sz && 0 <= y2 && y2 < grid_sz) // new grid bottom
            {
                if (tile_coords.first >= TIMES_ENLARGE - 1)
                {
                    continue;
                }

                ++tile_coords.first;
                x2 = 0;
            }

            Cell &next_cell = grid[x2][y2];
            int next_cost = (last_cell.cost + next_cell.risk + TABLE[tile_coords.first][tile_coords.second]) % 10;
            next_cost = (next_cost == 0 ? next_cost + 1 : next_cost);
            if (!next_cell.has_step || next_cost < next_cell.step.cost)
            {
                next_cell.has_step = true;

                next_cell.step = {{x2, y2}, next_cost};
                std::cout << "Considering " << x2 << ' ' << y2 << "..." << tile_coords.first << ' ' << tile_coords.second << ' ' << next_cost << '\n';
                frontier.push(next_cell.step);
            }
        }
    }

    return grid[goal_tile_coords.first][goal_tile_coords.second].step.cost;
}

void part1()
{
    int grid_sz = 0;
    Cell grid[GRID_CAP][GRID_CAP];
    parse(grid, grid_sz);
    std::cout << "Part 1: " << ucs_p1(grid, grid_sz) << '\n';
}

void part2()
{
    // parse grid
    int grid_sz = 0;
    Cell grid[GRID_CAP][GRID_CAP];
    parse(grid, grid_sz);

    // get path
    std::cout << "Part 2: " << ucs_p2(grid, grid_sz) << '\n';
}

int main(int argc, char const *argv[])
{
    part2();

    return 0;
}
