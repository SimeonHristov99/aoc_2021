#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

std::vector<std::string> get_data(const char *filename)
{
    std::vector<std::string> result;
    std::ifstream fin("input.txt");
    std::string buffer;

    if (!fin)
    {
        std::cout << "ERROR: Could not open file!\n";
        return {};
    }

    while (std::getline(fin, buffer))
    {
        result.push_back(buffer);
    }

    fin.close();

    return result;
}

void get_distribution_of_ones(const std::vector<std::string> &data, std::vector<int> &ones, const int len_bits)
{
    ones = std::vector<int>(len_bits, 0);

    for (const std::string &measure : data)
    {
        for (int j = 0; j < len_bits; ++j)
        {
            if (measure[j] == '1')
            {
                ++ones[j];
            }
        }
    }
}

unsigned int part1(const std::vector<std::string> &data)
{
    unsigned int gamma = 0;

    int len_data = data.size();
    int len_bits = data[0].size();
    
    std::vector<int> ones;
    get_distribution_of_ones(data, ones, len_bits);

    unsigned int offset = 32 - len_bits;

    for (int i = 0; i < len_bits; ++i)
    {
        if (ones[i] > len_data - ones[i])
        {
            gamma ^= (1 << (len_bits - 1 - i));
        }
    }

    return gamma * (~gamma << offset >> offset);
}

template <typename T, typename Pred>
std::vector<T> filter(const std::vector<T> &xs, Pred p)
{
    std::vector<T> result;

    for (const T &x : xs)
    {
        if (p(x))
        {
            result.push_back(x);
        }
    }

    return result;
}

unsigned int get_rating(std::vector<std::string> &data, std::vector<int> &ones, int len_bits, char default_keep)
{
    for (int i = 0; i < len_bits && data.size() > 1; ++i)
    {
        char c = (ones[i] >= data.size() - ones[i] ? default_keep : (default_keep == '0' ? '1' : '0'));
        data = filter(data, [i, c](const std::string &s)
                      { return s[i] == c; });
        get_distribution_of_ones(data, ones, len_bits);
    }

    return std::stoi(data[0], 0, 2);
}

unsigned int part2(const std::vector<std::string> &data)
{
    std::vector<std::string> oxygen = data;
    std::vector<std::string> co2 = data;

    int len_bits = data[0].size();
    std::vector<int> ones_oxygen;
    get_distribution_of_ones(data, ones_oxygen, len_bits);
    std::vector<int> ones_co2 = ones_oxygen;

    unsigned int oxygen_rate = get_rating(oxygen, ones_oxygen, len_bits, '1');
    unsigned int co2_rate = get_rating(co2, ones_co2, len_bits, '0');

    return oxygen_rate * co2_rate;
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> data = get_data("input.txt");

    std::cout << "Part 1: " << part1(data) << '\n';
    std::cout << "Part 2: " << part2(data) << '\n';

    return 0;
}
