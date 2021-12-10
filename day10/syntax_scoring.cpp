#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>
#include <vector>

#if 0
const char *filename = "sample.txt";
#else
const char *filename = "input.txt";
#endif

long validate(const std::string &input, bool score_incorrect = true)
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
                if (s.top() != '(')
                {
                    return (score_incorrect ? 3 : 0);
                }
                break;
            }
            case ']':
            {
                if (s.top() != '[')
                {
                    return (score_incorrect ? 57 : 0);
                }
                break;
            }
            case '}':
            {
                if (s.top() != '{')
                {
                    return (score_incorrect ? 1197 : 0);
                }
                break;
            }
            case '>':
            {
                if (s.top() != '<')
                {
                    return (score_incorrect ? 25137 : 0);
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

    if (!score_incorrect && s.size() > 0)
    {
        long score = 0;

        while (!s.empty())
        {
            switch (s.top())
            {
            case '(':
            {
                score = score * 5 + 1;
                break;
            }
            case '[':
            {
                score = score * 5 + 2;
                break;
            }
            case '{':
            {
                score = score * 5 + 3;
                break;
            }
            case '<':
            {
                score = score * 5 + 4;
                break;
            }
            }

            s.pop();
        }

        return score;
    }

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

long part2()
{
    std::ifstream fin(filename);
    if (!fin)
    {
        printf("ERROR: Could not open %s\n", filename);
        return -1;
    }

    std::vector<long> scores;
    std::string buffer;

    while (std::getline(fin, buffer))
    {
        long score = validate(buffer, false);
        if (score > 0)
        {
            scores.push_back(score);
        }
    }

    fin.close();

    std::sort(scores.begin(), scores.end());

    return scores[scores.size() / 2];
}

int main(int argc, char const *argv[])
{
    printf("Part 1: %d\n", part1());
    printf("Part 2: %ld\n", part2());

    return 0;
}
