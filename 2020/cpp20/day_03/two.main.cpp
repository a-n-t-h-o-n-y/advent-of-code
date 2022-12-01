#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>

#include "common.hpp"

int main()
{
    auto file  = std::ifstream{"../day_03/input.txt"};
    auto count = [&file](std::pair<int, int> hv) {
        return count_trees(reset(file), hv.first, hv.second);
    };

    auto const patterns = std::array{
        std::pair{1, 1}, std::pair{3, 1}, std::pair{5, 1},
        std::pair{7, 1}, std::pair{1, 2},
    };

    auto const result =
        std::transform_reduce(std::begin(patterns), std::end(patterns), 1uL,
                              std::multiplies{}, count);
    std::cout << result << '\n';
}
