#include <fstream>
#include <iostream>

#include "common.hpp"

int main()
{
    auto const values = [] {
        auto file = std::ifstream{"../day_01/input.txt"};
        return read_values(file);
    }();
    if (auto const r = find_ternary_sum_operands(values, 2020); r)
        std::cout << r->first * r->second * r->third << '\n';
}
