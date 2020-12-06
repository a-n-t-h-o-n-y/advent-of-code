#include <fstream>
#include <iostream>

#include "common.hpp"

// Find the two entries that sum to 2020;
// what do you get if you multiply them together?

auto main() -> int
{
    auto const values = [] {
        auto file = std::ifstream{"../day_01/input.txt"};
        return read_values(file);
    }();
    if (auto const r = find_binary_sum_operands(values, 2020); r)
        std::cout << r->first * r->second << '\n';
}
