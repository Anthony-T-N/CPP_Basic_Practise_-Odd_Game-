#include <iostream>

void board_generation(int size)
{
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
