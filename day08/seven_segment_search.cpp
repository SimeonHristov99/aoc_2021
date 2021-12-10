#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

#if 0
const char *filename = "sample.txt";
#else
const char *filename = "input.txt";
#endif

const int BUFFER_SZ = 100;
const int AFTER_DELIM_SZ = 4;
const int BEFORE_DELIM_SZ = 10;

void part1()
{
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << filename << '\n';
        return;
    }

    char *buffer = new char[BUFFER_SZ];
    char *buffer_start = buffer;
    int numbers[AFTER_DELIM_SZ];
    int result = 0;

    while (fin.getline(buffer, BUFFER_SZ))
    {
        while (*buffer != '|')
        {
            ++buffer;
        }
        ++buffer;

        do
        {
            ++buffer;

            char *start = buffer;
            while (*buffer && isalpha(*buffer))
            {
                ++buffer;
            }

            if (buffer - start == 2 || buffer - start == 3 || buffer - start == 4 || buffer - start == 7)
            {
                ++result;
            }
        } while (*buffer);

        buffer = buffer_start;
    }

    fin.close();
    delete[] buffer_start;
    buffer_start = nullptr;

    std::cout << "Part 1: " << result << '\n';
}

bool elem(const char x, const std::string &s)
{
    for (const char c : s)
    {
        if (c == x)
        {
            return true;
        }
    }
    return false;
}

int elems_containing(const char x, const std::vector<std::string> values)
{
    int result = 0;

    for (const std::string &s : values)
    {
        if (elem(x, s))
        {
            ++result;
        }
    }

    return result;
}

char get_unique_element(const std::string &v1, const std::string &v2)
{
    for (const char c : v2)
    {
        bool seen = false;
        for (const char x : v1)
        {
            if (c == x)
            {
                seen = true;
                break;
            }
        }
        if (!seen)
        {
            return c;
        }
    }
    std::cout << "Unreachable\n";
    return 'x';
}

std::string remove_characters(const std::string &in, const std::string &from)
{
    std::string result;

    for (const char c : in)
    {
        if (!elem(c, from))
        {
            result += c;
        }
    }

    return result;
}

void build_segments(std::vector<std::string> &values, char *segments)
{
    std::sort(values.begin(), values.end(), [](const std::string &s1, const std::string &s2)
              { return s1.length() < s2.length(); });

    if (elems_containing(values[0][0], values) > elems_containing(values[0][1], values))
    {
        segments[1] = values[0][1];
        segments[2] = values[0][0];
    }
    else
    {
        segments[1] = values[0][0];
        segments[2] = values[0][1];
    }

    segments[0] = get_unique_element(values[0], values[1]);

    std::string left_mid = remove_characters(values[2], values[0]);

    if (elems_containing(left_mid[0], values) > elems_containing(left_mid[1], values))
    {
        segments[5] = left_mid[1];
        segments[6] = left_mid[0];
    }
    else
    {
        segments[5] = left_mid[0];
        segments[6] = left_mid[1];
    }

    std::string bottom_left = remove_characters(values[values.size() - 1], values[2] + values[1]);

    if (elems_containing(bottom_left[0], values) > elems_containing(bottom_left[1], values))
    {
        segments[3] = bottom_left[0];
        segments[4] = bottom_left[1];
    }
    else
    {
        segments[3] = bottom_left[1];
        segments[4] = bottom_left[0];
    }
}

int get_value(const std::string &s, const char *segments)
{
    std::vector<std::string> values{
        "1111110",
        "0110000",
        "1101101",
        "1111001",
        "0110011",
        "1011011",
        "1011111",
        "1110000",
        "1111111",
        "1111011",
    };

    std::string activations(7, '0');

    for (const char c : s)
    {
        for (int i = 0; i < 7; ++i)
        {
            if (c == segments[i])
            {
                activations[i] = '1';
                break;
            }
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        if (values[i] == activations)
        {
            return i;
        }
    }

    std::cout << "Unreachable!\n";
    return -1;
}

int get_output_value(const std::vector<std::string> &values_after, const char *segments)
{
    int result = 0;

    for (const std::string &s : values_after)
    {
        result = result * 10 + get_value(s, segments);
    }

    return result;
}

void part2()
{
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open " << filename << '\n';
        return;
    }

    std::string buffer;
    int result = 0;

    while (std::getline(fin, buffer))
    {
        char segments[7] = {'\0'}; // 0:TOP, 1:TOPRIGHT, 2:BOTTOMRIGHT, 3:BOTTOM, 4:BOTTOMLEFT, 5:TOPLEFT, 6:MIDDLE

        std::vector<std::string> values_before;
        std::vector<std::string> values_after;

        bool saw_delim = false;
        std::string value;

        for (const char c : buffer)
        {
            if (isalpha(c))
            {
                value += c;
            }
            else if (c == '|')
            {
                saw_delim = true;
            }
            else if (value.size() > 1)
            {
                if (!saw_delim)
                {
                    values_before.push_back(value);
                }
                else
                {
                    values_after.push_back(value);
                }

                value = "";
            }
        }
        values_after.push_back(value);

        build_segments(values_before, segments);

        result += get_output_value(values_after, segments);
    }

    fin.close();

    std::cout << "Part 2: " << result << '\n';
}

int main()
{
    part1();
    part2();

    return 0;
}
