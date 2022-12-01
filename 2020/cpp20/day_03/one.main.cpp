#include <fstream>
#include <iostream>

#include "common.hpp"

int main()
{
    auto file = std::ifstream{"../day_03/input.txt"};
    std::cout << count_trees(file, 3) << '\n';
}
