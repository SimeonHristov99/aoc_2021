#include <iostream>
#include <fstream>

#if 0
const char *filename = "sample.txt";
const int BOARD_SIZE = 10;
#else
const char *filename = "input.txt";
const int BOARD_SIZE = 1000;
#endif

void parse(const std::string &buffer, int board[][BOARD_SIZE], bool include_diag)
{
    std::string number;

    int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
    int spaces = 0;

    int len_buffer = buffer.size();
    for (const char c : buffer)
    {
        if (c == ',')
        {
            switch (spaces)
            {
            case 0:
                x1 = atoi(number.c_str());
                break;
            case 2:
                x2 = atoi(number.c_str());
                break;
            default:
                std::cout << "Unreachable spaces: " << spaces << '\n';
                return;
            }

            number = "";
        }
        else if (c == ' ')
        {
            switch (spaces)
            {
            case 0:
                y1 = atoi(number.c_str());
                break;
            case 1:
                break;
            default:
                std::cout << "Unreachable spaces: " << spaces << '\n';
                return;
            }

            number = "";
            ++spaces;
        }
        else if (isdigit(c))
        {
            number += c;
        }
    }

    y2 = atoi(number.c_str());

    int min_x = std::min(x1, x2);
    int max_x = std::max(x1, x2);

    int min_y = std::min(y1, y2);
    int max_y = std::max(y1, y2);

    if (include_diag && max_x - min_x == max_y - min_y)
    {
        int row_start = min_y;
        int col_start = (y1 == min_y ? x1 : x2);
        int col_end = (y1 == min_y ? x2 : x1);

        for(int i = min_y; i <= max_y; ++i)
        {
            ++board[i][col_start];
            
            col_start += (col_start < col_end ? 1 : -1);
        }

        return;
    }

    if (!(x1 == x2 || y1 == y2))
    {
        return;
    }

    for (int i = min_y; i <= max_y; ++i)
    {
        for (int j = min_x; j <= max_x; ++j)
        {
            ++board[i][j];
        }
    }
}

size_t count_overlaps(int board[][BOARD_SIZE])
{
    size_t result = 0;

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j] > 1)
            {
                ++result;
            }
        }
    }

    return result;
}

size_t build_board(bool include_diag = false)
{
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "ERROR: Could not open file.\n";
        return 0;
    }

    std::string buffer;
    int board[BOARD_SIZE][BOARD_SIZE] = {{0}};

    while (std::getline(fin, buffer))
    {
        parse(buffer, board, include_diag);
    }

    return count_overlaps(board);
}

int main(int argc, char const *argv[])
{
    std::cout << "Part 1: " << build_board(false) << '\n';
    std::cout << "Part 2: " << build_board(true) << '\n';

    return 0;
}
