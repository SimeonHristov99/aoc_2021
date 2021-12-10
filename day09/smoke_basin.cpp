#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>

#if 0
const char *filename = "sample.txt";
const int MAP_SIZE = 10;
#else
const char *filename = "input.txt";
const int MAP_SIZE = 100;
#endif

void dump_map(const int map[][MAP_SIZE], int w, int h)
{
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            std::cout << map[i][j];
        }
        std::cout << '\n';
    }
}

void parse(int map[][MAP_SIZE], int *h, int *w)
{
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << filename << '\n';
        return;
    }

    std::string buffer;
    fin >> buffer;
    *w = buffer.length();

    do
    {
        for (int i = 0; i < *w; ++i)
        {
            map[*h][i] = buffer[i] - '0';
        }

        ++*h;
    } while (fin >> buffer);
}

int part1(const int map[][MAP_SIZE], const int w, const int h, std::queue<std::pair<int, int>> &coords)
{
    int result = 0;

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (!(
                    i - 1 >= 0 && map[i][j] >= map[i - 1][j] || i + 1 < h && map[i][j] >= map[i + 1][j] || j - 1 >= 0 && map[i][j] >= map[i][j - 1] || j + 1 < w && map[i][j] >= map[i][j + 1]))
            {
                result += map[i][j] + 1;
                coords.push({i, j});
            }
        }
    }

    return result;
}

int part2(const int map[][MAP_SIZE], const int w, const int h, std::queue<std::pair<int, int>> &coords)
{
    std::vector<int> sizes;

    while (!coords.empty())
    {
        std::pair<int, int> front = coords.front();
        coords.pop();

        std::stack<std::pair<int, int>> frontier;
        std::set<std::pair<int, int>> visited;
        frontier.push(front);

        while (!frontier.empty())
        {
            int i = frontier.top().first;
            int j = frontier.top().second;
            // std::cout << i << ' ' << j << '\n';
            visited.insert({i, j});
            frontier.pop();

            if (i - 1 >= 0 && map[i-1][j] != 9 && visited.find({i - 1, j}) == visited.end())
            {
                frontier.push({i - 1, j});
            }

            if (i + 1 < h && map[i+1][j] != 9 && visited.find({i + 1, j}) == visited.end())
            {
                frontier.push({i + 1, j});
            }

            if (j - 1 >= 0 && map[i][j-1] != 9 && visited.find({i, j - 1}) == visited.end())
            {
                frontier.push({i, j - 1});
            }

            if (j + 1 < w && map[i][j+1] != 9 && visited.find({i, j + 1}) == visited.end())
            {
                frontier.push({i, j + 1});
            }
        }

        sizes.push_back(visited.size());
    }

    std::sort(sizes.begin(), sizes.end(), std::greater<int>());

    return sizes[0] * sizes[1] * sizes[2];
}

int main(int argc, char const *argv[])
{
    int map[MAP_SIZE][MAP_SIZE];
    int h = 0, w = 0;
    std::queue<std::pair<int, int>> coords;

    parse(map, &h, &w);

    std::cout << "Part 1: " << part1(map, w, h, coords) << '\n';

    std::cout << "Part 2: " << part2(map, w, h, coords) << '\n';

    return 0;
}
