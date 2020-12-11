#ifndef DAY_11_COMMON_HPP
#define DAY_11_COMMON_HPP
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

auto parse(std::istream& is) -> std::vector<int>
{
    auto result = std::vector<int>{};
    std::ranges::copy(std::ranges::istream_view<int>(is),
                      std::back_inserter(result));
    return result;
}

auto solution_1(std::string const& filename) -> int
{
    auto file   = std::ifstream(filename);
    auto values = parse(file);
    return 0;
}

// Part II ---------------------------------------------------------------------

auto solution_2(std::string const& filename) -> int
{
    auto file   = std::ifstream(filename);
    auto values = parse(file);
    return 0;
}

#endif  // DAY_11_COMMON_HPP
