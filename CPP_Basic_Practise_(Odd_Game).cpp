#include <iostream>
#include <vector>
#include <sstream>

// std::vector == Dynamic array (Similar to C# lists)
// 2D Vectory array.
std::vector<std::vector<std::string>> main_board;

void board_generation(int &size)
{
    std::vector<std::string> board_sector;
   
    /*
    for (int j = 0; j < size; j++)
    {
        board_sector.push_back("[" + std::to_string(j + 1) + "]");
    }
    main_board.push_back(board_sector);
    */
    for (int i = 0; i < size; i++)
    {
        board_sector.clear();
        // board_sector.push_back("[" + std::to_string(i + 1) + "]");
        for (int j = 0; j < size; j++)
        {
            board_sector.push_back("[ ]");
        }
        main_board.push_back(board_sector);
    }
    // Print board.
    for (int i = 0; i < main_board.size(); i++)
    {
        for (int j = 0; j < main_board[i].size(); j++)
        {
            std::cout << main_board[i][j];
        }
        std::cout << "\n";
    }
}

void item_positioning()
{
    main_board[4][7] = "[@]";
}

int main()
{
    std::cout << "Welcome friend!" << "\n\n";
    int board_size;
    std::cin >> board_size;
    board_generation(board_size);
    std::cout << "\n\n";
    item_positioning();
    for (int i = 0; i < main_board.size(); i++)
    {
        for (int j = 0; j < main_board[i].size(); j++)
        {
            std::cout << main_board[i][j];
        }
        std::cout << "\n";
    }
    return 0;
}
