#ifndef DAY_01_COMMON_HPP
#define DAY_01_COMMON_HPP
#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <utility>
#include <vector>

/// Grab ints from stream separated by whitespace
inline auto read_values(std::istream& is) -> std::vector<int>
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

struct Triplet {
    int first;
    int second;
    int third;
};

/// Find the first three elements in \p values that add up to \p sum.
template <typename Container>
auto find_ternary_sum_operands(Container const& values, int sum)
    -> std::optional<Triplet>
{
    auto const end = std::cend(values);
    for (auto front = std::cbegin(values); front != end; ++front) {
        for (auto middle = std::next(front); middle != end; ++middle) {
            auto const diff = sum - *front - *middle;
            auto const back = std::find(std::next(middle), end, diff);
            if (back != end)
                return Triplet{*front, *middle, *back};
        }
    }
    return std::nullopt;
}

#endif  // DAY_01_COMMON_HPP
