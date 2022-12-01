#ifndef DAY_05_COMMON_HPP
#define DAY_05_COMMON_HPP
#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>

/// Copies all chars from \p sv into an array of chars, must be 10 chars or less
inline auto to_array(std::string_view sv) -> std::array<char, 10>
{
    auto chars = std::array<char, 10>{};
    std::ranges::copy(sv, std::begin(chars));
    return chars;
}

/// Each line parsed into an array of chars, 10 chars in length.
inline auto to_arrays(std::istream& is) -> std::vector<std::array<char, 10>>
{
    auto result = std::vector<std::array<char, 10>>{};
    // clang-format off
    std::ranges::copy(
        std::ranges::istream_view<std::string>(is)
        | std::ranges::views::transform(to_array),
        std::back_inserter(result)
    );
    // clang-format on
    return result;
}

/// Return the lower or upper half of \p range, negative direction is lower.
auto halve_range(auto range, int direction) -> std::pair<int, int>
{
    auto const half_size = (range.second - range.first + 1) / 2;
    if (direction < 0)
        return {range.first, range.second - half_size};
    else
        return {range.second - half_size + 1, range.second};
}

inline auto get_direction(char c) -> int
{
    switch (c) {
        case 'B':
        case 'R': return 1;
        case 'F':
        case 'L': return -1;
    }
    return 0;
}

/// Converts binary search instructions into a row, column seat position.
/** Returns a struct with .row and .column members. */
inline auto to_row_column(std::array<char, 10> const& instructions)
{
    struct Result {
        int row;
        int column;
    };
    auto constexpr max_rows    = 127;
    auto constexpr max_columns = 7;

    auto row_range = std::pair{0, max_rows};
    for (auto i = 0; i < 7; ++i)
        row_range = halve_range(row_range, get_direction(instructions[i]));

    auto col_range = std::pair{0, max_columns};
    for (auto i = 7; i < 10; ++i)
        col_range = halve_range(col_range, get_direction(instructions[i]));

    return Result{row_range.first, col_range.first};
}

/// Turns a seat position into a seat id.
auto to_seat_id(auto position) -> int
{
    return (position.row * 8) + position.column;
}

/// Finds the largest seat id from the input file
inline auto solution_1(std::string const& filename) -> int
{
    namespace rv = std::ranges::views;
    auto file    = std::ifstream{filename};
    auto arrays  = to_arrays(file);
    // clang-format off
    return
        std::ranges::max(
            rv::all(arrays)
            | rv::transform(to_row_column)
            | rv::transform([](auto rc){ return to_seat_id(rc); })
    );
    // clang-format on
}

/// Find your seat ID.
inline auto solution_2(std::string const& filename) -> int
{
    namespace rv = std::ranges::views;
    auto file    = std::ifstream{filename};
    auto arrays  = to_arrays(file);
    auto ids     = std::set<int>{};
    // clang-format off
    std::ranges::copy(
        rv::all(arrays)
        | rv::transform(to_row_column)
        | rv::transform([](auto rc){ return to_seat_id(rc); }),
        std::inserter(ids, std::begin(ids))
    );
    // clang-format on

    auto iter = std::adjacent_find(std::begin(ids), std::end(ids),
                                   [](auto x, auto y) { return x + 1 != y; });
    if (iter == std::end(ids))
        throw 5;
    return *iter + 1;
}

#endif  // DAY_05_COMMON_HPP
