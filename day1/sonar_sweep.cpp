#include <iostream>
#include <fstream>
#include <vector>

int part1(const std::vector<int> &depths)
{
    int times_increased = 0;
    int len_depths = depths.size();

    for (int i = 0; i < len_depths - 1; ++i)
    {
        if (depths[i] < depths[i + 1])
        {
            ++times_increased;
        }
    }

    return times_increased;
}

int part2(const std::vector<int> &depths)
{
    std::vector<int> sums;

    int len_depths = depths.size();
    for (int i = 0; i < len_depths - 2; i++)
    {
        sums.push_back(depths[i] + depths[i + 1] + depths[i + 2]);
    }

    return part1(sums);
}

int main(int argc, char const *argv[])
{
    std::vector<int> parsed_input;
    std::ifstream fin("input.txt");
    int x = -1;

    // Read in the data.
    if (!fin)
    {
        std::cout << "ERROR: Could not open file!\n";
        return -1;
    }

    // Parse the data.
    while (fin >> x)
    {
        parsed_input.push_back(x);
    }
    fin.close();

    std::cout << part1(parsed_input) << '\n';
    std::cout << part2(parsed_input) << '\n';

    return 0;
}
