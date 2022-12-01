#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

/// Read from \p filename into a vector of strings, breaking on newline.
auto file_to_lines(auto const& filename) -> std::vector<std::string>
{
    auto file  = std::ifstream{filename};
    auto lines = std::ranges::istream_view<std::string>(file);
    auto v     = std::vector<std::string>{};
    std::ranges::copy(lines, std::back_inserter(v));
    return v;
}

auto count_trees(auto const& lines, auto deltas) -> int
{
    namespace rv      = std::ranges::views;
    auto const width  = lines.front().size();
    int const height  = lines.size();
    auto const [x, y] = deltas;
    // clang-format off
    return std::ranges::distance(
          rv::iota(0, height / y)
        | rv::transform([&](auto e) { return std::pair{e * y, (e * x) % width}; })
        | rv::transform([&](auto e) { return lines[e.first][e.second]; })
        | rv::filter([](auto x) { return x == '#'; }));
    // clang-format on
}

// Part II using std::ranges
int main()
{
    auto const lines = file_to_lines("../day_03/input.txt");

    auto count = [&lines](auto deltas) { return count_trees(lines, deltas); };

    auto const patterns = std::array{
        std::pair{1, 1}, std::pair{3, 1}, std::pair{5, 1},
        std::pair{7, 1}, std::pair{1, 2},
    };

    auto const result =
        std::transform_reduce(std::begin(patterns), std::end(patterns), 1uL,
                              std::multiplies{}, count);

    std::cout << result << '\n';
}
