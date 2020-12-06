#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <utility>
#include <vector>

// Find the two entries that sum to 2020;
// what do you get if you multiply them together?

/// Grab ints from stream separated by whitespace
auto read_values(std::istream& is) -> std::vector<int>
{
    auto v = std::vector<int>{};
    auto i = 0;
    while (is >> i)
        v.push_back(i);
    return v;
}

/// Find the first two elements in \p values that add up to \p sum.
template <typename Container>
auto find_binary_sum_operands(Container const& values, int sum)
    -> std::optional<std::pair<int, int>>
{
    auto const end = std::cend(values);
    for (auto front = std::cbegin(values); front != end; ++front) {
        auto const diff = sum - *front;
        auto const at   = std::find(std::next(front), end, diff);
        if (at != end)
            return std::pair{*front, *at};
    }
    return std::nullopt;
}

/// Find the first two elements in \p values that add up to \p sum.
template <typename Container>
auto find_binary_sum_operands_alt(Container const& values, int sum)
    -> std::optional<std::pair<int, int>>
{
    for (auto i = 0uL; i < values.size(); ++i) {
        auto const diff = sum - values[i];
        for (auto j = i + 1; j < values.size(); ++j) {
            if (values[j] == diff)
                return std::pair{values[i], values[j]};
        }
    }
    return std::nullopt;
}

auto main() -> int
{
    auto const values = [] {
        auto file = std::ifstream{"../day_01/input.txt"};
        return read_values(file);
    }();
    if (auto const r = find_binary_sum_operands(values, 2020); r)
        std::cout << r->first * r->second << '\n';
}
