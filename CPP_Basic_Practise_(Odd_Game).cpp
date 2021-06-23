#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>

// std::vector == Dynamic array (Similar to C# lists)
// 2D Vectory array.
std::vector<std::vector<std::string>> main_board;
// Current position of player. (Main Character / Current Player)
int main_position_one, main_position_two;
// Current position of T. (Tracker)
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
            board_sector.push_back(" . ");
        }
        main_board.push_back(board_sector);
    }
    board_display();
    
}

void item_positioning(int size)
{
    // https://stackoverflow.com/questions/4919303/c-random-number-generation
    // Generate number between 0 and size.
    for (int i = 0; i <= 5; i++)
    {
        main_board[rand() % (size)][rand() % (size)] = "[#]";
        main_board[rand() % (size)][rand() % (size)] = "[!]";
        main_board[rand() % (size)][rand() % (size)] = "[%]";
    }
    main_position_one = rand() % (size);
    main_position_two = rand() % (size);
    std::cout << main_position_one << "|" << main_position_two << "\n\n";
    main_board[main_position_one][main_position_two] = "[@]";
    tracker_position_one = rand() % (size);
    tracker_position_two = rand() % (size);
    // Detect if tracker spawns at the same position of main character.
    while (main_position_one == tracker_position_one && main_position_two == tracker_position_two)
    {
        std::cout << "[-] Tracker spawn conflict detected;" << "\n";
        tracker_position_one = rand() % (size);
        tracker_position_two = rand() % (size);
    }
    main_board[tracker_position_one][tracker_position_two] = "[T]";
}

void deploy_shield(std::string& user_input)
{
    if (user_input == "w")
    {
        if (main_position_one - 1 < 0)
        {
            std::cout << "[-] Beyond Boundary Error" << "\n";
        }
        else
        {
            main_board[main_position_one - 1][main_position_two - 1] = " # ";
            main_board[main_position_one - 1][main_position_two] = " # ";
            main_board[main_position_one - 1][main_position_two + 1] = " # ";
        }
    }
    else if (user_input == "s")
    {
        if (main_position_one + 1 >= main_board.size())
        {
            std::cout << "[-] Beyond Boundary Error" << "\n";
        }
        else
        {
            main_board[main_position_one + 1][main_position_two - 1] = " # ";
            main_board[main_position_one + 1][main_position_two] = " # ";
            main_board[main_position_one + 1][main_position_two + 1] = " # ";
        }
    }
    else if (user_input == "d")
    {
        if (main_position_two + 1 >= main_board.size())
        {
            std::cout << "[-] Beyond Boundary Error" << "\n";
        }
        else
        {
            main_board[main_position_one - 1][main_position_two + 1] = " # ";
            main_board[main_position_one][main_position_two + 1] = " # ";
            main_board[main_position_one + 1][main_position_two + 1] = " # ";
        }
    }
    else if (user_input == "a")
    {
        if (main_position_two - 1 < 0)
        {
            std::cout << "[-] Beyond Boundary Error" << "\n";
        }
        else
        {
            main_board[main_position_one - 1][main_position_two - 1] = " # ";
            main_board[main_position_one][main_position_two - 1] = " # ";
            main_board[main_position_one + 1][main_position_two - 1] = " # ";
        }
    }
}

void tracker()
{
    std::cout << "Tracker moving" << "\n";
    main_board[tracker_position_one][tracker_position_two] = " . ";
    int random_pos_one = rand() % (2);
    std::cout << random_pos_one << "\n";
    // Top Left
    if (tracker_position_one > main_position_one && tracker_position_two > main_position_two)
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
    else if (tracker_position_one > main_position_one && tracker_position_two < main_position_two)
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
    else if (tracker_position_one < main_position_one && tracker_position_two > main_position_two)
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
    else if (tracker_position_one < main_position_one && tracker_position_two < main_position_two)
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
    else if (tracker_position_one == main_position_one && tracker_position_two < main_position_two)
    {
        tracker_position_two += 1;
    }
    // Left
    else if (tracker_position_one == main_position_one && tracker_position_two > main_position_two)
    {
        tracker_position_two -= 1;
    }
    // Down
    else if (tracker_position_one < main_position_one && tracker_position_two == main_position_two)
    {
        tracker_position_one += 1;
    }
    // Up
    else if (tracker_position_one > main_position_one && tracker_position_two == main_position_two)
    {
        tracker_position_one -= 1;
    }
    main_board[tracker_position_one][tracker_position_two] = "[T]";
}

int player_control(std::string& user_input)
{
    // Remove main character from current position.
    main_board[main_position_one][main_position_two] = " . ";

    int movement = 1;

    if (user_input == "z")
    {
        std::cout << "Direction: ";
        std::cin >> user_input;
        deploy_shield(user_input);
        main_board[main_position_one][main_position_two] = "[@]";
        return 0;
    }

    if (user_input == "t")
    {
        std::cout << "Direction: ";
        std::cin >> user_input;
        movement = 5;
    }
    // Move left.
    if (user_input == "w")
    {
        if (main_position_one - movement < 0)
        {
            std::cout << "[-] Beyond Boundary Error" << "\n";
        }
        else
        {
            // Move main character on board up by one.
            main_position_one -= movement;
        }
    }
    // Move down.
    else if (user_input == "s")
    {
        if (main_position_one + movement >= (main_board.size()))
        {
            std::cout << "[-] Beyond Boundary Error" << "\n";
        }
        else
        {
            // Move main character on board down by one.
            main_position_one += movement;
        }
    }
    // Move right.
    else if (user_input == "d")
    {
        if (main_position_two + movement >= (main_board.size()))
        {
            std::cout << "[-] Beyond Boundary Error" << "\n";
        }
        else
        {
            // Move main character on board right by one.
            main_position_two += movement;
        }
    }
    // Move up.
    else if (user_input == "a")
    {
        if (main_position_two - movement < 0)
        {
            std::cout << "[-] Beyond Boundary Error" << "\n";
        }
        else
        {
            // Move main character on board left by one.
            main_position_two -= movement;
        }
    }
    else if (user_input == "exit")
    {
        std::cout << "User wants to exit;" << "\n";
        return 1;
    }
    else
    {
        std::cout << "[-] Invalid User Input;" << "\n";
        main_board[main_position_one][main_position_two] = "[@]";
        return 0;
    }
    main_board[main_position_one][main_position_two] = "[@]";
    return 0;
}

// =====================================================================================
// Experimental
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
//#include <mmsystem.h>
void soundtrack()
{
    // https://stackoverflow.com/questions/28656004/c-random-doesnt-workreturns-same-value-always
    srand(time(NULL));
    std::string play_track = "";
    if (0 == rand() % 2)
    {
        play_track = "Mixdown.wav";
        PlaySound(TEXT("Mixdown.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }
    else
    {
        play_track = "E2T4.wav";
        PlaySound(TEXT("E2T4.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }
    std::cout << "Playing Track: " << play_track << "\n";
}
// =====================================================================================

int main()
{
    std::cout << "=======================================" << "\n";
    std::cout << "- CPP_Basic_Practise_(Odd_Game) console application" << "\n";
    std::cout << "- Console Application Version: 1.0" << "\n";
    std::cout << "- Created By: Anthony N." << "\n";
    // https://en.cppreference.com/w/cpp/filesystem/current_path
    std::cout << "- Current location of executable: " << std::filesystem::current_path() << "\n";
    std::cout << "=======================================" << "\n\n";
    // Never trust user input.
    soundtrack();
    std::cout << "Welcome friend!" << "\n\n";
    std::cout << "Controls:" << "\n";
    std::cout << "WASD to move" << "\n";
    std::cout << "t to teleport" << "\n";
    std::cout << "z to deploy shield" << "\n";
    std::cout << "[@] <= Your character" << "\n";
    std::cout << "[T] <= Tracker" << "\n";
    std::cout << "Type 'Exit' to end application" << "\n\n";
    std::cout << "Please enter board size: ";
    int board_size;
    //TODO: Ensure user input is always a number.
    std::cin >> board_size;
    board_generation(board_size);
    std::cout << "\n\n";
    item_positioning(board_size);
    board_display();
    while (true)
    {
        std::string user_input;
        std::cout << "User input: ";
        std::cin >> user_input;
        if (player_control(user_input) == 1)
        {
            break;
        }
        tracker();
        std::cout << "Main character: " << main_position_one << "|" << main_position_two 
            << " Tracker: " << tracker_position_one << "|" << tracker_position_two << "\n";
        board_display();
        if (main_position_one == tracker_position_one && main_position_two == tracker_position_two)
        {
            std::cout << "[-] GAME OVER;" << "\n";
            break;
        }
    }
    std::cout << "[!] END" << "\n";
    std::cout << "[!] Exiting..." << "\n\n";
    return 0;
}
