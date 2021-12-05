#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

typedef std::pair<int, bool> BoardElement;
typedef std::vector<BoardElement> Board;

void parse_drawn_numbers(const std::string &input, std::vector<int> &result)
{
    std::string number;

    for (const char c : input)
    {
        if (c == ',')
        {
            result.push_back(atoi(number.c_str()));
            number = "";
        }
        else
        {
            number += c;
        }
    }
    result.push_back(atoi(number.c_str()));
}

void parse_board(const std::string &input, std::vector<Board> &boards)
{
    std::string number;

    Board b;

    for (const char c : input)
    {
        if (isdigit(c))
        {
            number += c;
        }
        else if (number.size() > 0)
        {
            b.push_back({atoi(number.c_str()), false});
            number = "";
        }
    }

    boards.push_back(b);
}

void parse(const char *filename, std::vector<int> &drawn, std::vector<Board> &boards, int &num_rows)
{
    std::ifstream fin("input.txt");
    assert(fin);

    std::string buffer;
    std::getline(fin, buffer);

    parse_drawn_numbers(buffer, drawn);

    std::getline(fin, buffer);
    std::string board;

    while (std::getline(fin, buffer))
    {
        if (buffer == "")
        {
            parse_board(board, boards);
            board = "";
            num_rows = 0;
        }
        else
        {
            board += buffer += '\n';
            ++num_rows;
        }
    }

    fin.close();
    parse_board(board, boards);
}

void update_board(const int number, Board &b)
{
    for (BoardElement &be : b)
    {
        if (be.first == number)
        {
            be.second = true;
        }
    }
}

bool check_board(const Board &b, const int num_rows)
{
    int num_cols = b.size() / num_rows;

    for (int i = 0; i < b.size(); i += num_rows)
    {
        bool wins = true;

        for (int j = 0; j < num_cols; ++j)
        {
            if (!b[i + j].second)
            {
                wins = false;
            }
        }

        if (wins)
        {
            return wins;
        }
    }

    for (int i = 0; i < num_cols; ++i)
    {
        bool wins = true;

        for (int j = 0; i + j < b.size(); j += num_cols)
        {
            if (!b[i + j].second)
            {
                wins = false;
                break;
            }
        }

        if (wins)
        {
            return wins;
        }
    }

    return false;
}

int sum_unmarked(const Board &b)
{
    int result = 0;

    for (const BoardElement &x : b)
    {
        if (!x.second)
        {
            result += x.first;
        }
    }

    return result;
}

int get_winning_score(const std::vector<int> drawn, std::vector<Board> &boards, const int num_rows, bool first)
{
    for (const int number : drawn)
    {
        for (int i = 0; i < boards.size(); ++i)
        {
            update_board(number, boards[i]);
            if (check_board(boards[i], num_rows))
            {
                if(first)
                {
                    return number * sum_unmarked(boards[i]);
                }

                if (boards.size() == 1)
                {
                    return number * sum_unmarked(boards[0]);
                }

                boards.erase(boards.begin() + i);
                --i;
            }
        }
    }

    return -1;
}

int main(int argc, char const *argv[])
{
    std::vector<int> drawn;
    std::vector<Board> boards;
    int num_rows = 0;

    parse("input.txt", drawn, boards, num_rows);

    std::cout << "Part 1: " << get_winning_score(drawn, boards, num_rows, true) << '\n';
    std::cout << "Part 2: " << get_winning_score(drawn, boards, num_rows, false) << '\n';

    return 0;
}
