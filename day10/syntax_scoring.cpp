#include <iostream>
#include <fstream>
#include <stack>

#if 0
const char *filename = "sample.txt";
const int INPUT_SZ = 25;
#else
const char *filename = "input.txt";
const int INPUT_SZ = 110;
#endif

int validate(const std::string &input, bool get_score=true)
{
    std::stack<char> s;

    for (const char c : input)
    {
        if (c == '(' || c == '[' || c == '{' || c == '<')
        {
            s.push(c);
        }
        else if (c == ')' || c == ']' || c == '}' || c == '>')
        {
            switch (c)
            {
            case ')':
            {
                if (get_score && s.top() != '(')
                {
                    return 3;
                }
                break;
            }
            case ']':
            {
                if (get_score && s.top() != '[')
                {
                    return 57;
                }
                break;
            }
            case '}':
            {
                if (get_score && s.top() != '{')
                {
                    return 1197;
                }
                break;
            }
            case '>':
            {
                if (get_score && s.top() != '<')
                {
                    return 25137;
                }
                break;
            }
            }

            s.pop();
        }
        else
        {
            printf("Unreachable: %c\n", c);
            return -1;
        }
    }

    // if(s.size() > 0)
    // {
    //     printf("Size: %ld", s.size());
    // }

    return 0;
}

int part1()
{
    std::ifstream fin(filename);
    if (!fin)
    {
        printf("ERROR: Could not open %s\n", filename);
        return -1;
    }

    int score = 0;
    std::string buffer;

    while (std::getline(fin, buffer))
    {
        score += validate(buffer);
    }

    fin.close();

    return score;
}

int part2()
{
    std::ifstream fin(filename);
    if (!fin)
    {
        printf("ERROR: Could not open %s\n", filename);
        return -1;
    }

    int score = 0;
    std::string buffer;

    while (std::getline(fin, buffer))
    {
        score += validate(buffer, false);
        return -1;
    }

    fin.close();

    return score;
}

int main(int argc, char const *argv[])
{
    printf("Part 1: %d\n", part1());
    // printf("Part 2: %d\n", part2());

    return 0;
}
