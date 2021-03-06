#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>

#if 0
const char *filename = "sample.txt";
#else
const char *filename = "input.txt";
#endif

void parse(std::vector<std::pair<std::string, std::string>> &paths)
{
    std::ifstream fin(filename);
    if (!fin)
    {
        printf("ERROR: Could not open %s\n", filename);
    }

    std::string buffer;

    while (fin >> buffer)
    {
        std::pair<std::string, std::string> pair;

        int i = 0;
        for (; buffer[i] != '-'; ++i)
        {
            pair.first += buffer[i];
        }

        ++i;
        for (; buffer[i]; ++i)
        {
            pair.second += buffer[i];
        }

        paths.push_back(pair);
    }

    fin.close();
}

bool is_lowercase(const std::string &s)
{
    int len_s = s.length();
    for (int i = 0; i < len_s; ++i)
    {
        if (!islower(s[i]))
        {
            return false;
        }
    }
    return true;
}

std::vector<std::string> get_all_continuations(const std::string &from, const std::vector<std::pair<std::string, std::string>> &paths)
{
    std::vector<std::string> result;

    for (const std::pair<std::string, std::string> &p : paths)
    {
        if (p.first == from || p.second == from)
        {
            result.push_back((p.first != from ? p.first : p.second));
        }
    }

    return result;
}

bool visited(const std::string &n, const std::vector<std::string> &xs, int max_visits = 1)
{
    int visits = 0;

    for (const std::string &x : xs)
    {
        if (x == n)
        {
            ++visits;
        }
    }

    return visits >= max_visits;
}

int part1()
{
    int result = 0;
    std::vector<std::pair<std::string, std::string>> paths;

    parse(paths);

    std::queue<std::vector<std::string>> frontier;
    std::vector<std::vector<std::string>> ress;

    frontier.push({"start"});

    while (!frontier.empty())
    {
        std::vector<std::string> top = frontier.front();
        frontier.pop();
        std::string last_el = top[top.size() - 1];

        if (last_el == "end")
        {
            ress.push_back(top);
        }

        std::vector<std::string> continuations = get_all_continuations(last_el, paths);
        for (const std::string &continuation : continuations)
        {
            if (!is_lowercase(continuation) || !visited(continuation, top))
            {
                top.push_back(continuation);
                frontier.push(top);
                top.pop_back();
            }
        }
    }

    return ress.size();
}

int visits(const std::string &n, const std::vector<std::string> &xs)
{
    int count = 0;

    for (const std::string &x : xs)
    {
        if (x == n)
        {
            ++count;
        }
    }

    return count;
}

int part2()
{
    int result = 0;
    std::vector<std::pair<std::string, std::string>> paths;

    parse(paths);

    std::queue<std::pair<std::vector<std::string>, bool>> frontier;
    std::vector<std::vector<std::string>> ress;

    frontier.push({{"start"}, false});

    while (!frontier.empty())
    {
        std::pair<std::vector<std::string>, bool> top = frontier.front();
        frontier.pop();
        std::string last_el = top.first[top.first.size() - 1];

        if (last_el == "end")
        {
            ress.push_back(top.first);
        }

        std::vector<std::string> continuations = get_all_continuations(last_el, paths);
        for (const std::string &continuation : continuations)
        {
            if (continuation == "end" && visits(continuation, top.first) == 1 || continuation == "start" && visits(continuation, top.first) == 1)
            {
                continue;
            }

            if (!is_lowercase(continuation))
            {
                top.first.push_back(continuation);
                frontier.push(top);
                top.first.pop_back();
            }
            else if (top.second && visits(continuation, top.first) < 1)
            {
                top.first.push_back(continuation);
                frontier.push(top);
                top.first.pop_back();
            }
            else if (!top.second)
            {
                int num_visited = visits(continuation, top.first);

                if (num_visited >= 1)
                {
                    top.first.push_back(continuation);
                    top.second = true;
                    frontier.push(top);
                    top.second = false;
                    top.first.pop_back();
                }
                else
                {
                    top.first.push_back(continuation);
                    frontier.push(top);
                    top.first.pop_back();
                }
            }
        }
    }

    return ress.size();
}

int main(int argc, char const *argv[])
{
    printf("Result: %d\n", part1());
    printf("Result: %d\n", part2());

    return 0;
}
