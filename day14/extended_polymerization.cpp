#include <iostream>
#include <fstream>
#include <vector>

#if 0
const char *filename = "sample.txt";
const int INSERTIONS_CAP = 16;
#else
const char *filename = "input.txt";
const int INSERTIONS_CAP = 100;
#endif

const int STEPS = 10;

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

struct Insertion
{
    std::string pair;
    char value;
};

void parse(std::string &polymer_template, Insertion insertions[INSERTIONS_CAP], size_t &size)
{
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << filename << '\n';
        return;
    }

    std::string buffer;

    std::getline(fin, buffer);
    polymer_template = buffer;
    std::getline(fin, buffer);

    while (std::getline(fin, buffer))
    {
        std::string leftover = split_by_delim(buffer, ' ', insertions[size].pair);
        std::string tmp;
        insertions[size++].value = split_by_delim(leftover, ' ', tmp)[0];
    }

    fin.close();
}

void dump_insertions(Insertion insertions[INSERTIONS_CAP], size_t &size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << insertions[i].pair << " -> " << insertions[i].value << '\n';
    }
}

void breed(std::string &polymer_template, Insertion insertions[INSERTIONS_CAP], const size_t size)
{
    for (int epoch = 0; epoch < STEPS; ++epoch)
    {
        std::string new_template;
        int len_polymer = polymer_template.length();
        for (int i = 0; i < len_polymer - 1; ++i)
        {
            std::string current_pair{polymer_template[i], polymer_template[i + 1]};

            for (int j = 0; j < size; ++j)
            {
                if (insertions[j].pair == current_pair)
                {
                    current_pair.insert(1, 1, insertions[j].value);
                    current_pair.pop_back();
                    // std::cout << current_pair << '\n';
                    new_template += current_pair;
                    break;
                }
            }
        }
        polymer_template = new_template += polymer_template[len_polymer - 1];
        // std::cout << polymer_template << '\n';
    }
}

void get_distribution(std::vector<int> &distrib, std::string &polymer_template)
{
    int min = 1000000, max = 0;

    while (!polymer_template.empty())
    {
        int num_erased = std::erase(polymer_template, polymer_template[0]);

        if(num_erased > max)
        {
            max = num_erased;
        }
        
        if(num_erased < min && num_erased > 1)
        {
            min = num_erased;
        }
    }

    std::cout << "Part 1: " << max - min << '\n';
}

void part1()
{
    std::string polymer_template;
    Insertion insertions[INSERTIONS_CAP];
    size_t size = 0;

    parse(polymer_template, insertions, size);

    // std::cout << polymer_template << '\n';
    // dump_insertions(insertions, size);

    breed(polymer_template, insertions, size);

    std::vector<int> distrib;
    get_distribution(distrib, polymer_template);
}

int main(int argc, char const *argv[])
{
    part1();

    return 0;
}
