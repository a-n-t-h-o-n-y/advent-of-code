#ifndef DAY_03_COMMON_HPP
#define DAY_03_COMMON_HPP
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>

/// Get a single line of text from \p is. Return std::nullopt if \p is is empty.
inline auto getline(std::istream& is) -> std::optional<std::string>
{
    auto result = std::string{};
    if (std::getline(is, result, '\n'))
        return result;
    return std::nullopt;
}

/// Get the char at \p index, allowing access past the end by wrapping to length
/** Not valid to call with empty strings. */
inline auto wrapping_at(std::size_t index, std::string const& s) -> char
{
    return s[index % s.size()];
}

/// Count the number of trees encountered with given step pattern.
inline auto count_trees(std::istream& input,
                        int horizontal_step,
                        int vertical_step = 1) -> int
{
    auto constexpr tree = '#';

    auto count   = 0;
    auto h_index = 0;
    auto v_index = 0;
    while (auto const line = getline(input)) {
        ++v_index;
        if (((v_index - 1) % vertical_step) != 0)
            continue;
        count += wrapping_at(h_index, *line) == tree ? 1 : 0;
        h_index += horizontal_step;
    }
    return count;
}

/// Reset \p is to the beginning of the stream and return a ref to it.
inline auto reset(std::istream& is) -> std::istream&
{
    is.clear();
    is.seekg(0);
    return is;
}

#endif  // DAY_03_COMMON_HPP
