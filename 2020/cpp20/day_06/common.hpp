#ifndef DAY_06_COMMON_HPP
#define DAY_06_COMMON_HPP
#include <algorithm>
#include <fstream>
#include <functional>
#include <numeric>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <vector>

/// Splits input on "\n\n".
inline auto split_on_nlnl(std::istream& file) -> std::vector<std::string>
{
    auto result = std::vector<std::string>{};
    while (file) {
        auto group    = std::string{};
        char c        = '\0';
        auto nl_count = 0;
        while (nl_count != 2 && file.get(c)) {
            group.push_back(c);
            nl_count = c == '\n' ? nl_count + 1 : 0;
        }
        group.pop_back();
        result.push_back(std::move(group));
    }
    return result;
}

/// Put each char into a std::set and return. Strips '\n'.
inline auto to_set(std::string_view sv) -> std::set<char>
{
    namespace rv = std::ranges::views;
    auto result  = std::set<char>{};
    // clang-format off
    std::ranges::copy(
        rv::all(sv) | rv::filter([](char c){ return c != '\n'; }),
        std::inserter(result, std::begin(result))
    );
    // clang-format on
    return result;
}

auto get_size(auto const& x) -> int { return x.size(); }

/// Return the count of the total number of questions answered yes by all groups
inline auto solution_1(std::string const& filename) -> int
{
    namespace rv      = std::ranges::views;
    auto file         = std::ifstream{filename};
    auto const groups = split_on_nlnl(file);
    // clang-format off
    auto const counts = rv::all(groups)
                        | rv::transform(to_set)
                        | rv::transform([](auto const& x){ return get_size(x); });
    // clang-format on
    return std::reduce(std::cbegin(counts), std::cend(counts), 0, std::plus{});
}

// Part II

inline auto to_string_vector(std::string const& in) -> std::vector<std::string>
{
    auto result = std::vector<std::string>{};
    auto ss     = std::istringstream{in};
    std::ranges::copy(std::ranges::istream_view<std::string>(ss),
                      std::back_inserter(result));
    return result;
}

inline auto to_set_vector(std::vector<std::string> const& strings)
    -> std::vector<std::set<char>>
{
    namespace rv = std::ranges::views;
    auto result  = std::vector<std::set<char>>{};
    std::ranges::copy(rv::all(strings) | rv::transform(to_set),
                      std::back_inserter(result));
    return result;
}

inline auto conjunction(std::set<char> const& a, std::set<char> const& b)
    -> std::set<char>
{
    namespace rv = std::ranges::views;
    auto r       = std::set<char>{};
    std::ranges::copy(
        rv::all(b) | rv::filter([&a](char c) { return a.contains(c); }),
        std::inserter(r, std::begin(r)));
    return r;
}

inline auto to_char_conjunction(std::vector<std::set<char>> const& answers)
    -> std::set<char>
{
    static auto const init = [] {
        auto r = std::set<char>{};
        for (auto i = 'a'; i <= 'z'; ++i)
            r.insert(i);
        return r;
    }();
    return std::reduce(std::cbegin(answers), std::cend(answers), init,
                       conjunction);
}

/// Return the count of the number of yes answers by everyone in all groups.
inline auto solution_2(std::string const& filename) -> int
{
    namespace rv      = std::ranges::views;
    auto file         = std::ifstream{filename};
    auto const groups = split_on_nlnl(file);

    // clang-format off
    auto const counts = rv::all(groups)
                        | rv::transform(to_string_vector)
                        | rv::transform(to_set_vector)
                        | rv::transform(to_char_conjunction)
                        | rv::transform([](auto const& x){ return get_size(x); });
    // clang-format on
    return std::reduce(std::cbegin(counts), std::cend(counts), 0, std::plus{});
}

#endif  // DAY_06_COMMON_HPP
