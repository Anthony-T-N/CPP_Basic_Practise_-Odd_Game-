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
int tracker_position_x, tracker_position_y;

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
        // Integer division by zero error here.
        main_board[rand() % (size)][rand() % (size)] = "[#]";
        main_board[rand() % (size)][rand() % (size)] = "[!]";
        main_board[rand() % (size)][rand() % (size)] = "[%]";
    }
    main_position_one = rand() % (size);
    main_position_two = rand() % (size);
    std::cout << main_position_one << "|" << main_position_two << "\n\n";
    main_board[main_position_one][main_position_two] = "[@]";
    tracker_position_x = rand() % (size);
    tracker_position_y = rand() % (size);
    // Detect if tracker spawns at the same position of main character.
    while (main_position_one == tracker_position_x && main_position_two == tracker_position_y)
    {
        std::cout << "[-] Tracker spawn conflict detected;" << "\n";
        tracker_position_x = rand() % (size);
        tracker_position_y = rand() % (size);
    }
    main_board[tracker_position_x][tracker_position_y] = "[T]";
}

void deploy_shield(std::string& user_input)
{
    if (user_input == "w")
    {
        if (main_position_one - 1 < 0 || main_position_two - 1 < 0 || main_position_two + 1 >= main_board.size())
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
        if (main_position_one + 1 >= main_board.size() || main_position_two - 1 < 0 || main_position_two + 1 >= main_board.size())
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
        if (main_position_two + 1 >= main_board.size() || main_position_one - 1 < 0 || main_position_one + 1 >= main_board.size())
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
        if (main_position_two - 1 < 0 || main_position_one - 1 < 0 || main_position_one + 1 >= main_board.size())
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

bool break_shield(std::string axis, int pos_neg)
{
    bool stop_tracker = false;
    std::cout << "SHIELD BREAK" << "\n";
    if (axis == "x")
    {
        if (main_board[tracker_position_x + pos_neg][tracker_position_y] == " # ")
        {
            std::cout << "X BLOCK" << "\n";
            main_board[tracker_position_x + pos_neg][tracker_position_y] = " = ";
            stop_tracker = true;
        }
        else if (main_board[tracker_position_x + pos_neg][tracker_position_y] == " = ")
        {
            std::cout << "X BLOCK" << "\n";
            main_board[tracker_position_x + pos_neg][tracker_position_y] = " . ";
            stop_tracker = true;
        }
    }
    else if (axis == "y")
    {
        std::cout << "Debug: break_shield " << axis << " " << pos_neg << "\n";
        if (main_board[tracker_position_x][tracker_position_y + pos_neg] == " # ")
        {
            std::cout << "Y BLOCK" << "\n";
            main_board[tracker_position_x][tracker_position_y + pos_neg] = " = ";
            stop_tracker = true;
        }
        else if (main_board[tracker_position_x][tracker_position_y + pos_neg] == " = ")
        {
            std::cout << "Y BLOCK" << "\n";
            main_board[tracker_position_x][tracker_position_y + pos_neg] = " . ";
            stop_tracker = true;
        }
    }
    return stop_tracker;
}

void tracker()
{
    std::cout << "Tracker moving" << "\n";
    main_board[tracker_position_x][tracker_position_y] = " . ";
    int random_pos_one = rand() % (2);
    // Top Left
    if (tracker_position_x > main_position_one && tracker_position_y > main_position_two)
    {
        if (random_pos_one == 0)
        {
            //break_shield("x", -1);
            tracker_position_x -= 1;
        }
        else
        {
            //break_shield("y", -1);
            tracker_position_y -= 1;
        }
    }
    // Top right
    else if (tracker_position_x > main_position_one && tracker_position_y < main_position_two)
    {
        if (random_pos_one == 0)
        {
            tracker_position_x -= 1;
        }
        else
        {
            tracker_position_y += 1;
        }
    }
    // Bottom Left
    else if (tracker_position_x < main_position_one && tracker_position_y > main_position_two)
    {
        if (random_pos_one == 0)
        {
            tracker_position_x += 1;
        }
        else
        {
            tracker_position_y -= 1;
        }
    }
    // Bottom Right
    else if (tracker_position_x < main_position_one && tracker_position_y < main_position_two)
    {
        if (random_pos_one == 0)
        {
            tracker_position_x += 1;
        }
        else
        {
            tracker_position_y += 1;
        }
    }
    // Right
    else if (tracker_position_x == main_position_one && tracker_position_y < main_position_two)
    {
        if (break_shield("y", 1) == false)
        {
            tracker_position_y += 1;
        }
    }
    // Left
    else if (tracker_position_x == main_position_one && tracker_position_y > main_position_two)
    {
        if (break_shield("y", -1) == false)
        {
            tracker_position_y -= 1;
        }
    }
    // Down
    else if (tracker_position_x < main_position_one && tracker_position_y == main_position_two)
    {
        if (break_shield("x", 1) == false)
        {
            tracker_position_x += 1;
        }
    }
    // Up
    else if (tracker_position_x > main_position_one && tracker_position_y == main_position_two)
    {
        if (break_shield("x", -1) == false)
        {
            tracker_position_x -= 1;
        }
    }
    main_board[tracker_position_x][tracker_position_y] = "[T]";
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

void game_instructions()
{
    std::cout << "\n";
    std::cout << "> Controls:" << "\n";
    std::cout << "WASD to move" << "\n";
    std::cout << "t to teleport" << "\n";
    std::cout << "z to deploy shield" << "\n";
    std::cout << "Type 'Exit' to end application" << "\n\n";
    std::cout << "> Characters:" << "\n";
    std::cout << "[@] <= Your character" << "\n";
    std::cout << "[T] <= Tracker" << "\n\n";
    std::cout << "> Enter 't' and then enter a direction to teleport." << "\n";
    std::cout << " . . . . . . . | . . . . . . . " << "\n";
    std::cout << " . . . . . . . | . . . . . . . " << "\n";
    std::cout << " @ . . . . . . | . . . . . . @ " << "\n";
    std::cout << " . . . . . . . | . . . . . . . " << "\n";
    std::cout << " . . . . . . . | . . . . . . . " << "\n";
    std::cout << "===============================" << "\n";
    std::cout << "> Enter 'z' and then enter a direction to deploy a shield." << "\n";
    std::cout << "> Tracker spends a couple of turns breaking shield." << "\n";
    std::cout << " . . . . . . . | . . . . . . . | . . . . . . . " << "\n";
    std::cout << " . . . # . . . | . . . # . . . | . . . # . . . " << "\n";
    std::cout << " . . T # @ . . | . . T = . @ . | . . T . . . @ " << "\n";
    std::cout << " . . . # . . . | . . . # . . . | . . . # . . . " << "\n";
    std::cout << " . . . . . . . | . . . . . . . | . . . . . . . " << "\n\n";
}

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
    //soundtrack();
    std::cout << "Welcome friend!" << "\n\n";
    std::cout << "Instructions (y/n): " << "\n";
    char instructions;
    std::cin >> instructions;
    instructions = tolower(instructions);
    if (instructions == 'y')
    {
        game_instructions();
    }
    std::cout << "Please enter board size (int): ";
    std::string user_input;
    //TODO: Ensure user input is always a number.
    //TODO: Ensure user input is never 1.
    //TODO: Fix cases where input: <number><space><characters> accepted.
    std::cin >> user_input;
    while (std::cin.fail() || user_input.find_first_not_of("0123456789") != std::string::npos)
    {
        // https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
        // user didn't input a number
        std::cin.clear(); // Reset the failed state
        //std::cin.ignore(INT_MAX, '\n'); //skip bad input
        std::cin.ignore(256, '\n');
        // next, request user reinput
        std::cout << "Please enter board size (int): ";
        std::cin >> user_input;
        std::cout << user_input << "\n";
    }
    int board_size = stoi(user_input);
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
            << " Tracker: " << tracker_position_x << "|" << tracker_position_y << "\n";
        board_display();
        if (main_position_one == tracker_position_x && main_position_two == tracker_position_y)
        {
            std::cout << "[-] GAME OVER;" << "\n";
            break;
        }
    }
    std::cout << "[!] END" << "\n";
    std::cout << "[!] Exiting..." << "\n\n";
    return 0;
}
