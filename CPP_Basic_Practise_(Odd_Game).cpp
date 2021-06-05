#include <iostream>
#include <vector>
#include <sstream>

// std::vector == Dynamic array (Similar to C# lists)
// 2D Vectory array.
std::vector<std::vector<std::string>> main_board;
// Current position of player.
int position_one, position_two;

void board_generation(int &size)
{
    std::vector<std::string> board_sector;
   
    /*
    * // Adds row of number on top of board.
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

void item_positioning(int size)
{
    // Generate number between 0 and size.
    int random_pos_one = rand() % (size);
    int random_pos_two = rand() % (size);
    std::cout << random_pos_one << "|" << random_pos_two << "\n\n";
    main_board[random_pos_one][random_pos_two] = "[@]";
    position_one = random_pos_one;
    position_two = random_pos_two;
    for (int i = 0; i <= 5; i++)
    {
        main_board[rand() % (size)][rand() % (size)] = "[#]";
        main_board[rand() % (size)][rand() % (size)] = "[!]";
        main_board[rand() % (size)][rand() % (size)] = "[%]";
    }
}

void player_control(std::string& user_input)
{
    // Move left.
    if (user_input == "w")
    {
        // Remove main character from current position.
        main_board[position_one][position_two] = "[ ]";
        // Move main character on board up by one.
        position_one -= 1;
        main_board[position_one][position_two] = "[@]";
    }
    // Move down.
    else if (user_input == "s")
    {
        // Remove main character from current position.
        main_board[position_one][position_two] = "[ ]";
        // Move main character on board down by one.
        position_one += 1;
        main_board[position_one][position_two] = "[@]";
    }
    // Move right.
    else if (user_input == "d")
    {
        // Remove main character from current position.
        main_board[position_one][position_two] = "[ ]";
        // Move main character on board down by one.
        position_two += 1;
        main_board[position_one][position_two] = "[@]";
    }
    // Move up.
    else if (user_input == "a")
    {
        // Remove main character from current position.
        main_board[position_one][position_two] = "[ ]";
        // Move main character on board down by one.
        position_two -= 1;
        main_board[position_one][position_two] = "[@]";
    }
    else if (user_input == "exit")
    {
        return;
    }
    else
    {
        std::cout << "[-] Invalid User Input;" << "\n";
    }

}

int main()
{
    // Never trust user input.
    std::cout << "Welcome friend!" << "\n\n";
    int board_size;
    std::cin >> board_size;
    board_generation(board_size);
    std::cout << "\n\n";
    item_positioning(board_size);
    for (int i = 0; i < main_board.size(); i++)
    {
        for (int j = 0; j < main_board[i].size(); j++)
        {
            std::cout << main_board[i][j];
        }
        std::cout << "\n";
    }
    std::string user_input;
    while (true)
    {
        std::cin >> user_input;
        player_control(user_input);
        for (int i = 0; i < main_board.size(); i++)
        {
            for (int j = 0; j < main_board[i].size(); j++)
            {
                std::cout << main_board[i][j];
            }
            std::cout << "\n";
        }
    }
    return 0;
}
