#include <iostream>
#include <vector>
#include <sstream>

// std::vector == Dynamic array (Similar to C# lists)
// 2D Vectory array.
std::vector<std::vector<std::string>> main_board;
// Current position of player.
int position_one, position_two;
// Current position of V.
int tracker_position_one, tracker_position_two;

void board_display()
{
    // Prints out board.
    for (int i = 0; i < main_board.size(); i++)
    {
        for (int j = 0; j < main_board[i].size(); j++)
        {
            std::cout << main_board[i][j];
        }
        std::cout << "\n";
    }
}

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
    board_display();
    
}

void item_positioning(int size)
{
    // https://stackoverflow.com/questions/4919303/c-random-number-generation
    // Generate number between 0 and size.
    int random_pos_one = rand() % (size);
    int random_pos_two = rand() % (size);
    std::cout << random_pos_one << "|" << random_pos_two << "\n\n";
    main_board[random_pos_one][random_pos_two] = "[@]";
    position_one = random_pos_one;
    position_two = random_pos_two;
    random_pos_one = rand() % (size);
    random_pos_two = rand() % (size);
    main_board[random_pos_one][random_pos_two] = "[V]";
    tracker_position_one = random_pos_one;
    tracker_position_two = random_pos_two;
    for (int i = 0; i <= 5; i++)
    {
        main_board[rand() % (size)][rand() % (size)] = "[#]";
        main_board[rand() % (size)][rand() % (size)] = "[!]";
        main_board[rand() % (size)][rand() % (size)] = "[%]";
    }
}

void tracker()
{
    std::cout << "Tracker moving" << "\n";
    main_board[tracker_position_one][tracker_position_two] = "[ ]";
    int random_pos_one = rand() % (2);
    std::cout << random_pos_one << "\n";
    // Top Left
    if (tracker_position_one > position_one && tracker_position_two > position_two)
    {
        if (random_pos_one == 0)
        {
            tracker_position_one -= 1;
        }
        else
        {
            tracker_position_two -= 1;
        }
    }
    // Top right
    else if (tracker_position_one > position_one && tracker_position_two < position_two)
    {
        if (random_pos_one == 0)
        {
            tracker_position_one -= 1;
        }
        else
        {
            tracker_position_two += 1;
        }
    }
    // Bottom Left
    else if (tracker_position_one < position_one && tracker_position_two > position_two)
    {
        if (random_pos_one == 0)
        {
            tracker_position_one += 1;
        }
        else
        {
            tracker_position_two -= 1;
        }
    }
    // Bottom Right
    else if (tracker_position_one < position_one && tracker_position_two < position_two)
    {
        if (random_pos_one == 0)
        {
            tracker_position_one += 1;
        }
        else
        {
            tracker_position_two += 1;
        }
    }
    // Right
    else if (tracker_position_one == position_one && tracker_position_two < position_two)
    {
        tracker_position_two += 1;
    }
    // Left
    else if (tracker_position_one == position_one && tracker_position_two > position_two)
    {
        tracker_position_two -= 1;
    }
    // Down
    else if (tracker_position_one < position_one && tracker_position_two == position_two)
    {
        tracker_position_one += 1;
    }
    // Up
    else if (tracker_position_one > position_one && tracker_position_two == position_two)
    {
        tracker_position_one -= 1;
    }
    main_board[tracker_position_one][tracker_position_two] = "[V]";
}

int player_control(std::string& user_input)
{
    // Move left.
    if (user_input == "w")
    {
        // Remove main character from current position.
        main_board[position_one][position_two] = "[ ]";
        // Move main character on board up by one.
        position_one -= 1;
        main_board[position_one][position_two] = "[@]";
        return 0;
    }
    // Move down.
    else if (user_input == "s")
    {
        // Remove main character from current position.
        main_board[position_one][position_two] = "[ ]";
        // Move main character on board down by one.
        position_one += 1;
        main_board[position_one][position_two] = "[@]";
        return 0;
    }
    // Move right.
    else if (user_input == "d")
    {
        // Remove main character from current position.
        main_board[position_one][position_two] = "[ ]";
        // Move main character on board down by one.
        position_two += 1;
        main_board[position_one][position_two] = "[@]";
        return 0;
    }
    // Move up.
    else if (user_input == "a")
    {
        // Remove main character from current position.
        main_board[position_one][position_two] = "[ ]";
        // Move main character on board down by one.
        position_two -= 1;
        main_board[position_one][position_two] = "[@]";
        return 0;
    }
    else if (user_input == "exit")
    {
        std::cout << "User wants to exit;" << "\n";
        return 1;
    }
    else
    {
        std::cout << "[-] Invalid User Input;" << "\n";
        return 0;
    }
}

int main()
{
    // Never trust user input.
    std::cout << "Welcome friend!" << "\n\n";
    std::cout << "Board size: ";
    int board_size;
    // Ensure user input is always a number.
    std::cin >> board_size;
    board_generation(board_size);
    std::cout << "\n\n";
    item_positioning(board_size);
    board_display();
    std::string user_input;
    while (true)
    {
        std::cout << "User input: ";
        std::cin >> user_input;
        //int temp = player_control(user_input);
        if (player_control(user_input) == 1)
        {
            break;
        }
        tracker();
        std::cout << "Main character: " << position_one << "|" << position_two << "\n";
        std::cout << "Tracker: " << tracker_position_one << "|" << tracker_position_two << "\n";
        board_display();
    }
    std::cout << "[!] END" << "\n";
    std::cout << "[!] Exiting..." << "\n\n";
    return 0;
}
