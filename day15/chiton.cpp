#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#if 0
const char *FILENAME = "sample.txt";
const int GRID_CAP = 12;
#else
const char *FILENAME = "input.txt";
const int GRID_CAP = 128;
#endif

typedef std::pair<int, int> Cell;

void parse(int grid[][GRID_CAP], int &grid_sz)
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
            grid[i][j++] = c - '0';
        }
        ++i;
        j = 0;
    }

    fin.close();

    grid_sz = i;
}

void dump_grid(int grid[][GRID_CAP], int grid_sz)
{
    for (int i = 0; i < grid_sz; ++i)
    {
        for (int j = 0; j < grid_sz; ++j)
        {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

bool not_elem(const std::vector<Cell> &p, int i, int j)
{
    for (const Cell &c : p)
    {
        if (c.first == i && c.second == j)
        {
            return false;
        }
    }
    return true;
}

void bfs(int grid[][GRID_CAP], int grid_sz)
{
    auto cmp = [grid](
                   const std::vector<Cell> &p1,
                   const std::vector<Cell> &p2)
    {
        int p1s = 0, p2s = 0, p1z = p1.size(), p2z = p2.size();

        for (int i = 0; i < p1z; ++i)
        {
            p1s += grid[p1[i].first][p1[i].second];
        }

        for (int i = 0; i < p2z; ++i)
        {
            p2s += grid[p2[i].first][p2[i].second];
        }

        return p1s > p2s;
    };

    std::priority_queue<std::vector<Cell>, std::vector<std::vector<Cell>>, decltype(cmp)> frontier(cmp);
    std::vector<Cell> cheapest;

    frontier.push({{0, 0}});

    while (!frontier.empty())
    {
        cheapest = frontier.top();

        int cp_sz = cheapest.size();
        int i = cheapest[cp_sz - 1].first;
        int j = cheapest[cp_sz - 1].second;

        frontier.pop();

        if (i == grid_sz - 1 && j == grid_sz - 1)
        {
            break;
        }

        // up
        if (i - 1 >= 0 && not_elem(cheapest, i - 1, j))
        {
            std::vector<Cell> copy(cheapest);
            copy.push_back({i - 1, j});
            frontier.push(copy);
        }
        // right
        if (j + 1 < grid_sz && not_elem(cheapest, i, j + 1))
        {
            std::vector<Cell> copy(cheapest);
            copy.push_back({i, j + 1});
            frontier.push(copy);
        }
        // down
        if (i + 1 < grid_sz && not_elem(cheapest, i + 1, j))
        {
            std::vector<Cell> copy(cheapest);
            copy.push_back({i + 1, j});
            frontier.push(copy);
        }
        // left
        if (j - 1 >= 0 && not_elem(cheapest, i, j - 1))
        {
            std::vector<Cell> copy(cheapest);
            copy.push_back({i, j - 1});
            frontier.push(copy);
        }
    }

    int s = 0;
    for (const std::pair<int, int> &p : cheapest)
    {
        s += grid[p.first][p.second];
    }
    std::cout << s - grid[0][0] << '\n';
}

void part1()
{
    // parse the grid
    int grid_sz = 0;
    int grid[GRID_CAP][GRID_CAP];
    parse(grid, grid_sz);
    // dump_grid(grid, grid_sz);

    // BFS
    // std::cout << grid_sz << '\n';
    bfs(grid, grid_sz);
}

int main(int argc, char const *argv[])
{
    part1();

    return 0;
}
