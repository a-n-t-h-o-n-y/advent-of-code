#ifndef DAY_07_COMMON_HPP
#define DAY_07_COMMON_HPP
#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

using Color = std::string;

/// Number of bags of the given color.
struct Color_count {
    Color color;
    int count;
};

inline auto parse_subject_color(std::string_view line) -> std::string
{
    return std::string{line.substr(0, line.find(" bags"))};
}

inline auto skip_to_list(std::string_view line) -> std::string_view
{
    if (line.find("no other") != std::string_view::npos)
        return "";
    return line.substr(line.find("bags") + 13);
}

inline auto skip_to_next_item(std::string_view line) -> std::string_view
{
    auto const next = line.find(',');
    if (next == std::string_view::npos)
        return "";
    return line.substr(next + 2);
}

/// Parse an int, return std::nullopt if fails to parse.
inline auto parse_int(std::string_view x) -> std::optional<int>
{
    using std::errc;
    auto value         = 0;
    auto const [_, ec] = std::from_chars(x.data(), x.data() + x.size(), value);
    if (ec == errc::invalid_argument || ec == errc::result_out_of_range)
        return std::nullopt;
    return value;
}

inline auto get_count(std::string_view line) -> int
{
    auto const count = line.substr(0, line.find(' '));
    auto value       = 0;
    std::from_chars(count.data(), count.data() + count.size(), value);
    return value;
}

inline auto get_color(std::string_view line) -> Color
{
    auto const begin = line.find(' ') + 1;
    auto const end   = line.find(" bag");
    return Color{line.substr(begin, end - begin)};
}

inline auto parse_line(std::string_view line)
    -> std::pair<Color, std::vector<Color_count>>
{
    auto result  = std::pair<Color, std::vector<Color_count>>{};
    result.first = parse_subject_color(line);
    line         = skip_to_list(line);

    while (!line.empty()) {
        auto const count = get_count(line);
        auto const color = get_color(line);
        result.second.push_back(Color_count{color, count});
        line = skip_to_next_item(line);
    }
    return result;
}

using Rules = std::map<Color, std::vector<Color_count>>;

inline auto parse(std::istream& is) -> Rules
{
    auto result = Rules{};
    auto line   = std::string{};
    while (std::getline(is, line, '\n'))
        result.insert(parse_line(line));
    return result;
}

/// Return true if \p c is with a Color_count within \p colors
inline auto contains(Color c, std::vector<Color_count> const& colors) -> bool
{
    auto const at = std::ranges::find_if(
        colors, [&c](auto const& e) { return e.color == c; });
    return at != std::end(colors);
}

/// Return a vector of colors who directly contain \p c according to \p rules.
inline auto who_contains(Color c, Rules const& rules) -> std::vector<Color>
{
    auto result = std::vector<Color>{};
    for (auto const& [outer, inners] : rules)
        if (contains(c, inners))
            result.push_back(outer);
    return result;
}

/// Append elements from \p from to \p to, only if they are not already in \p to
inline void unique_append(std::vector<Color>& to, std::vector<Color> from)
{
    namespace rv = std::ranges::views;
    // clang-format off
    std::ranges::move(
        rv::all(from)
        | rv::filter([&to](auto const& c)
            { return std::ranges::find(to, c) == std::end(to); }),
        std::back_inserter(to)
    );
    // clang-format on
}

/// Count the total number of bag colors that can eventually contain \p c.
inline auto bag_color_count(Color const& c, Rules const& rules) -> int
{
    auto found = std::vector<Color>{c};
    auto index = 0uL;
    while (index != found.size()) {
        auto new_colors = who_contains(found[index], rules);
        unique_append(found, std::move(new_colors));
        ++index;
    }
    return found.size() - 1;
}

/// Return the number of bags that can eventually contain a shiny gold bag.
inline auto solution_1(std::string const& filename) -> int
{
    auto file  = std::ifstream{filename};
    auto rules = parse(file);
    return bag_color_count("shiny gold", rules);
}

// Part II

/// Counts the number of bags owned directly by \p c, according to \p rules.
inline auto count_direct_bags(Color const& c, Rules const& rules) -> int
{
    auto const& color_counts = rules.at(c);
    return std::accumulate(
        std::begin(color_counts), std::end(color_counts), 0,
        [](int total, Color_count const& x) { return total + x.count; });
}

/// Return the number of bags held within \p c, according to \p rules.
auto count_bags_within(Color const& c, Rules const& rules) -> int
{
    auto const color_counts = rules.at(c);
    auto sum                = 0;
    for (auto cc : color_counts)
        sum += cc.count * (count_bags_within(cc.color, rules) + 1);
    return sum;
}

/// Return the number of bags contained within a shiny gold bag.
inline auto solution_2(std::string const& filename) -> int
{
    auto file  = std::ifstream{filename};
    auto rules = parse(file);
    return count_bags_within("shiny gold", rules);
}

#endif  // DAY_07_COMMON_HPP
