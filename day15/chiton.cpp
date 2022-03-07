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
    int i;
    int j;
    int gn;
};

std::pair<int, int> NEIGHBOURS[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
inline size_t key(int i,int j) {return (size_t) i << 32 | (unsigned int) j;}

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

// bool not_elem(const std::vector<Cell> &p, int i, int j)
// {
//     for (const Cell &c : p)
//     {
//         if (c.first == i && c.second == j)
//         {
//             return false;
//         }
//     }
//     return true;
// }

int euclidean_distance(const Cell &cell, int sz)
{
    return std::sqrt((cell.i - sz) * (cell.i - sz) + (cell.j - sz) * (cell.j - sz));
}

void bfs(int grid[][GRID_CAP], int grid_sz)
{
    auto cmp = [grid_sz](const Cell &p1, const Cell &p2)
    {
        return p1.gn < p2.gn;
    };

    std::priority_queue<Cell, std::vector<Cell>, decltype(cmp)> frontier(cmp);
    std::unordered_map<size_t, int> visited;
    frontier.push({0, 0, 0});

    while (!frontier.empty())
    {
        Cell current_cell = frontier.top();
        frontier.pop();

        if (current_cell.i == grid_sz - 1 && current_cell.j == grid_sz - 1)
        {
            std::cout << current_cell.gn << '\n';
            return;
        }

        for(const std::pair<int, int> &neigh : NEIGHBOURS)
        {
            Cell next;
            next.i = current_cell.i + neigh.first;
            next.j = current_cell.j + neigh.second;

            if(next.i < 0 || next.j >= grid_sz)
            {
                continue;
            }

            next.gn = current_cell.gn + grid[next.i][next.j];
            std::unordered_map<size_t, int>::iterator seen_coords = visited.find(key(next.i, next.j));

            if(seen_coords != visited.end())
            {
                if (seen_coords->second < next.gn)
                {
                    frontier.push({next.i, next.j});
                }
            }

            
        }
    }
}

void part1()
{
    // parse the grid
    int grid_sz = 0;
    int grid[GRID_CAP][GRID_CAP];
    parse(grid, grid_sz);
    dump_grid(grid, grid_sz);

    // bfs(grid, grid_sz);
}

int main(int argc, char const *argv[])
{
    part1();

    return 0;
}
