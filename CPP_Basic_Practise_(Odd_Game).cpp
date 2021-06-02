#include <iostream>
#include <vector>

void board_generation(int size)
{
    // std::vector == Dynamic array (Similar to C# lists)

    std::vector<std::string> board;
    board.push_back({ "[ ]", "[ ]" , "[ ]" });

    for (int i = 0; i <= size - 1; i++)
    {
        for (int i = 0; i <= size - 1; i++)
        {
            std::cout << "[ ]";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

int main()
{
    std::cout << "Welcome friend!" << "\n\n";
    board_generation(10);
    return 0;
}
