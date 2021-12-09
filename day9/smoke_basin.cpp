#include <iostream>
#include <fstream>

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

void get_risk(const int map[][MAP_SIZE], int w, int h)
{
    int result = 0;

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (!(
                i - 1 >= 0 && map[i][j] >= map[i - 1][j]
                || i + 1 < h && map[i][j] >= map[i + 1][j]
                || j - 1 >= 0 && map[i][j] >= map[i][j - 1]
                || j + 1 < w && map[i][j] >= map[i][j + 1]
            ))
            {
                result += map[i][j] + 1;
            }
        }
    }

    std::cout << result << '\n';
}

void part1()
{
    int map[MAP_SIZE][MAP_SIZE];
    int h = 0, w = 0;

    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << filename << '\n';
        return;
    }

    std::string buffer;
    fin >> buffer;
    w = buffer.length();

    do
    {
        for (int i = 0; i < w; ++i)
        {
            map[h][i] = buffer[i] - '0';
        }

        ++h;
    } while (fin >> buffer);

    // dump_map(map, w, h);

    get_risk(map, w, h);
}

int main(int argc, char const *argv[])
{
    part1();

    return 0;
}
