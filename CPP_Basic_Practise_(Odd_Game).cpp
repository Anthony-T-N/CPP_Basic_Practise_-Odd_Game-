// -CPP_Basic_Practise_(Odd_Game)-.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void board_generation(int size)
{
    for (int i = 0; i <= size; i++)
    {
        std::cout << "[ ]" << "\n";
    }
}

int main()
{
    std::cout << "Welcome friend!" << "\n\n";
    board_generation(5);
    return 0;
}
