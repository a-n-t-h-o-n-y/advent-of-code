#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>

#include "common.hpp"

int main()
{
    auto file         = std::ifstream{"../day_03/input.txt"};
    auto const counts = std::array<int, 5>{
        count_trees(reset(file), 1, 1), count_trees(reset(file), 3, 1),
        count_trees(reset(file), 5, 1), count_trees(reset(file), 7, 1),
        count_trees(reset(file), 1, 2),
    };
    auto const result = std::reduce(std::begin(counts), std::end(counts),
                                    std::uint64_t{1}, std::multiplies{});
    std::cout << result << '\n';
}
