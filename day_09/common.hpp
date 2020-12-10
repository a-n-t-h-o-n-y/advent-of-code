#ifndef DAY_09_COMMON_HPP
#define DAY_09_COMMON_HPP
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ranges>
#include <span>
#include <string>
#include <vector>

inline auto parse(std::istream& is) -> std::vector<std::uint64_t>
{
    namespace rng = std::ranges;
    auto result   = std::vector<std::uint64_t>{};
    rng::copy(rng::istream_view<std::uint64_t>(is), std::back_inserter(result));
    return result;
}

/// Returns true if \p target is a sum of two of the \p numbers.
inline auto verify(std::span<std::uint64_t const> numbers, std::uint64_t target)
    -> bool
{
    for (auto i = 0uL; i < numbers.size(); ++i) {
        auto const diff = target - numbers[i];
        for (auto j = i + 1; j < numbers.size(); ++j) {
            if (numbers[j] == diff)
                return true;
        }
    }
    return false;
}

/// Return the first value that is not a sum of two of the previous 25.
inline auto find_incorrect_value(std::span<std::uint64_t const> numbers)
    -> std::uint64_t
{
    auto constexpr size = 25uL;
    auto begin          = 0uL;
    auto target_index   = size;
    while (verify(numbers.subspan(begin, size), numbers[target_index])) {
        ++begin;
        ++target_index;
    }
    return numbers[target_index];
}

// What is the first number that is not a sum of the previous 25 numbers.
inline auto solution_1(std::string const& filename) -> std::uint64_t
{
    auto file          = std::ifstream{filename};
    auto const numbers = parse(file);
    return find_incorrect_value(numbers);
}

// Part II

/// Return two indicies that demarcate a range that sums to target.
inline auto sum_range(std::span<std::uint64_t const> numbers,
                      std::uint64_t target)
    -> std::pair<std::size_t, std::size_t>
{
    auto begin = 0uL;
    auto end   = begin;
    auto sum   = numbers[0];
    while (sum != target) {
        if (sum < target) {
            ++end;
            sum += numbers[end];
        }
        else {
            sum -= numbers[begin];
            ++begin;
        }
    }
    return {begin, end};
}

inline auto solution_2(std::string const& filename) -> std::uint64_t
{
    auto constexpr invalid_number = std::uint64_t{552655238};

    auto file                = std::ifstream{filename};
    auto const numbers       = parse(file);
    auto const [first, last] = sum_range(numbers, invalid_number);
    auto const [min, max]    = std::minmax_element(std::begin(numbers) + first,
                                                std::begin(numbers) + last + 1);
    return *min + *max;
}

#endif  // DAY_09_COMMON_HPP
