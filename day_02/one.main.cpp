#include <fstream>
#include <iostream>
#include <string>

#include "common.hpp"

// How many passwords are valid according to their policies?
int main()
{
    auto count = 0;
    auto line  = std::string{};
    auto file  = std::ifstream{"../day_02/input.txt"};
    while (std::getline(file, line, '\n'))
        count += is_valid(line) ? 1 : 0;
    std::cout << count << '\n';
}
