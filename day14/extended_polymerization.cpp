#include <iostream>
#include <fstream>
#include <vector>

const char *FILENAME = "sample.txt";
const int SIZE = 26;
const int STEPS = 1;

void init_grid(int grid[][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            grid[i][j] = 0;
        }
    }
}

void parse(
    std::vector<std::string> &subs,
    int grid[][SIZE],
    int occurs[SIZE]
)
{
    std::string buffer, sub;
    std::ifstream fin(FILENAME);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << FILENAME << '\n';
        fin.close();
        return;
    }

    std::getline(fin, buffer);

    int len_buf = buffer.length();
    for (int i = 0; i < len_buf - 1; i++)
    {
        int from = buffer[i] - 'A';
        int to = buffer[i + 1] - 'A';
        
        ++grid[from][to];
        
        ++occurs[from];
    }
    ++occurs[buffer[len_buf - 1] - 'A'];

    std::getline(fin, buffer);

    while (std::getline(fin, buffer))
    {
        sub += buffer[0];
        sub += buffer[1];
        sub += buffer[6];

        subs.push_back(sub);
        sub = "";
    }

    fin.close();
}

void print_grid(int grid[][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void print_occurs(int occurs[SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        std::cout << occurs[i] << ' ';
    }
    std::cout << '\n';
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> subs;
    int occurs[SIZE] = { 0 };
    int grid[SIZE][SIZE];

    init_grid(grid);
    parse(subs, grid, occurs);

    for (int step = 0; step < STEPS; ++step)
    {
        std::vector<std::string> matched;

        // consider all pairs "simultaneously"
        for (const std::string &sub : subs)
        {
            if (grid[sub[0] - 'A'][sub[1] - 'A'] > 0)
            {
                matched.push_back(sub);
            }
        }

        for (const std::string &match : matched)
        {
            // insert new letter
            // NN, A
            // NAN
            ++grid[match[0] - 'A'][match[2] - 'A'];
            ++grid[match[2] - 'A'][match[1] - 'A'];

            // increment the occurences of the new element
            // grid[match[0] - 'A'][match[1] - 'A'] is the 
            // number of times we have this pair. We have to
            // insert the new letter for each of these pairs
            // occurs[match[2] - 'A'] += (occurs[match[2] - 'A'] == 0 ? 1 : 0);
            occurs[match[2] - 'A'] += grid[match[0] - 'A'][match[1] - 'A'];

            // disconnect pair
            grid[match[0] - 'A'][match[1] - 'A'] = 0;
        }
    }

    print_grid(grid);
    std::cout << "\nOccurs: ";
    print_occurs(occurs);


    return 0;
}