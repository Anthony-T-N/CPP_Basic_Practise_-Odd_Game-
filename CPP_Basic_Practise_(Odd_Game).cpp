#include <iostream>
#include <vector>

void board_generation(int size)
{
    // std::vector == Dynamic array (Similar to C# lists)
    // 2D Vectory array.
    std::vector<std::vector<std::string>> main_board;

    for (int i = 0; i < size; i++)
    {
        std::vector<std::string> board_sector;
        for (int j = 0; j < size; j++)
        {
            board_sector.push_back("[ ]");
        }
        main_board.push_back(board_sector);
    }
    for (int i = 0; i < main_board.size(); i++)
    {
        for (int j = 0; j < main_board[i].size(); j++)
        {
            std::cout << main_board[i][j];
        }
        std::cout << "\n";
    }
    /*
    for (int i = 0; i <= size - 1; i++)
    {
        for (int i = 0; i <= size - 1; i++)
        {
            std::cout << "[ ]";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
    */
}

int main()
{
    std::cout << "Welcome friend!" << "\n\n";
    board_generation(5);
    return 0;
}
