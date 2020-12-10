#ifndef DAY_10_COMMON_HPP
#define DAY_10_COMMON_HPP
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <span>
#include <string>
#include <vector>

#include <utility/memoize.hpp>

auto parse(std::istream& is) -> std::vector<int>
{
    namespace rng = std::ranges;
    auto result   = std::vector<int>{};
    rng::copy(rng::istream_view<int>(is), std::back_inserter(result));
    return result;
}

auto solution_1(std::string const& filename) -> int
{
    auto file   = std::ifstream{filename};
    auto values = parse(file);
    std::ranges::sort(values);
    values.insert(std::begin(values), 0);

    std::adjacent_difference(std::begin(values), std::end(values),
                             std::begin(values));
    values.front() = 3;  // your device has diff of 3, first entry is empty
    return std::count(std::begin(values), std::end(values), 1) *
           std::count(std::begin(values), std::end(values), 3);
}

// Part II

/// Return true if the difference is within the 1-3 range
auto verify(int a, int b) -> bool { return (b - a) <= 3; }

// Recursive solution with memoization.
auto solution_2(std::string const& filename) -> std::uint64_t
{
    auto file   = std::ifstream{filename};
    auto values = parse(file);
    std::ranges::sort(values);
    values.insert(std::begin(values), 0);
    values.push_back(values.back() + 3);

    auto memoized_count = utility::make_memoized<std::uint64_t(std::span<int>)>(
        [](auto& count, std::span<int> values) -> std::uint64_t {
            if (values.size() == 1)
                return 1;
            auto result = std::uint64_t{0};
            result += count(values.subspan(1));
            if (values.size() > 2 && verify(values[0], values[2])) {
                result += count(values.subspan(2));
                if (values.size() > 3 && verify(values[0], values[3]))
                    result += count(values.subspan(3));
            }
            return result;
        },
        [](std::span<int> const& s) { return s.size(); });

    return memoized_count(values);
}

#endif  // DAY_10_COMMON_HPP
