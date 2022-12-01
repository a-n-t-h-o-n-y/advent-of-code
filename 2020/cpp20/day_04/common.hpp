#ifndef DAY_04_COMMON_HPP
#define DAY_04_COMMON_HPP
#include <algorithm>
#include <cctype>
#include <charconv>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>

enum class Key { byr, iyr, eyr, hgt, hcl, ecl, pid, cid, Invalid };

/// Splits input on "\n\n".
inline auto get_passport_string(std::istream& file) -> std::string
{
    auto result   = std::string{};
    char c        = '\0';
    auto nl_count = 0;
    while (nl_count != 2 && file.get(c)) {
        result.push_back(c);
        nl_count = c == '\n' ? nl_count + 1 : 0;
    }
    return result;
}

inline auto to_key(std::string_view key) -> Key
{
    if (key == "byr")
        return Key::byr;
    if (key == "iyr")
        return Key::iyr;
    if (key == "eyr")
        return Key::eyr;
    if (key == "hgt")
        return Key::hgt;
    if (key == "hcl")
        return Key::hcl;
    if (key == "ecl")
        return Key::ecl;
    if (key == "pid")
        return Key::pid;
    if (key == "cid")
        return Key::cid;
    return Key::Invalid;
}

inline auto get_key(std::string_view key_value) -> Key
{
    return to_key(key_value.substr(0, 3));
}

// parse the keys out of the passport string.
inline auto parse_keys(std::string const& passport) -> std::set<Key>
{
    auto ss   = std::istringstream{passport};
    auto keys = std::set<Key>{};
    // clang-format off
    std::ranges::copy(
          std::ranges::istream_view<std::string>(ss)
        | std::ranges::views::transform(get_key),
        std::inserter(keys, std::begin(keys))
    );
    // clang-format on
    return keys;
}

inline auto parse_value(std::string_view kv) -> std::string
{
    return std::string{kv.substr(4)};
}

inline auto get_key_value(std::string_view kv) -> std::pair<Key, std::string>
{
    return {get_key(kv), parse_value(kv)};
}

inline auto parse_keys_values(std::string const& passport)
    -> std::map<Key, std::string>
{
    auto ss = std::istringstream{passport};
    auto kv = std::map<Key, std::string>{};
    // clang-format off
    std::ranges::copy(
          std::ranges::istream_view<std::string>(ss)
        | std::ranges::views::transform(get_key_value),
        std::inserter(kv, std::begin(kv))
    );
    // clang-format on
    return kv;
}

auto validate_keys(auto const& keys) -> bool
{
    if (keys.contains(Key::Invalid))
        return false;
    if (keys.size() == 8)
        return true;
    if (keys.size() == 7 && !keys.contains(Key::cid))
        return true;
    return false;
}

inline auto get_valid_count(std::string const& filename) -> int
{
    auto count = 0;
    auto file  = std::ifstream{filename};
    while (file) {
        auto const passport = get_passport_string(file);
        auto const keys     = parse_keys(passport);
        count += validate_keys(keys) ? 1 : 0;
    }
    return count;
}

// Part II
struct Birth_year {
    int year;
};
struct Issue_year {
    int year;
};
struct Expiration_year {
    int year;
};
struct Height {
    int value;
    std::string unit;
};
struct Hair_color {
    std::string color_value;
};
struct Eye_color {
    std::string color_name;
};
struct Passport_id {
    std::string id;
};

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

inline auto parse_birth_year(std::string_view x) -> std::optional<Birth_year>
{
    if (auto const i = parse_int(x); i)
        return Birth_year{*i};
    return std::nullopt;
}

inline auto parse_issue_year(std::string_view x) -> std::optional<Issue_year>
{
    if (auto const i = parse_int(x); i)
        return Issue_year{*i};
    return std::nullopt;
}

inline auto parse_expiration_year(std::string_view x)
    -> std::optional<Expiration_year>
{
    if (auto const i = parse_int(x); i)
        return Expiration_year{*i};
    return std::nullopt;
}

inline auto parse_height(std::string_view x) -> std::optional<Height>
{
    using std::errc;
    auto value         = 0;
    auto const [p, ec] = std::from_chars(x.data(), x.data() + x.size(), value);
    if (ec == errc::invalid_argument || ec == errc::result_out_of_range)
        return std::nullopt;
    return Height{value, std::string{p}};
}

inline auto parse_hair_color(std::string_view x) -> std::optional<Hair_color>
{
    if (x.size() != 7)
        return std::nullopt;
    return Hair_color{std::string{x}};
}

inline auto parse_eye_color(std::string_view x) -> std::optional<Eye_color>
{
    if (x.size() != 3)
        return std::nullopt;
    return Eye_color{std::string{x}};
}

inline auto parse_passport_id(std::string_view x) -> std::optional<Passport_id>
{
    if (x.size() != 9)
        return std::nullopt;
    return Passport_id{std::string{x}};
}

inline auto validate(Birth_year x) -> bool
{
    return x.year >= 1920 && x.year <= 2002;
}

inline auto validate(Issue_year x) -> bool
{
    return x.year >= 2010 && x.year <= 2020;
}

inline auto validate(Expiration_year x) -> bool
{
    return x.year >= 2020 && x.year <= 2030;
}

inline auto validate(Height x) -> bool
{
    if (x.unit == "cm")
        return x.value >= 150 && x.value <= 193;
    if (x.unit == "in")
        return x.value >= 59 && x.value <= 76;
    return false;
}

inline auto validate(Hair_color x) -> bool
{
    if (x.color_value[0] != '#')
        return false;
    return std::ranges::all_of(x.color_value.substr(1),
                               [](auto c) { return std::isalnum(c); });
}

inline auto validate(Eye_color x) -> bool
{
    auto constexpr allowed =
        std::array{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    auto const at = std::ranges::find(allowed, x.color_name);
    return at != std::end(allowed);
}

inline auto validate(Passport_id x) -> bool
{
    return std::ranges::all_of(x.id, [](auto c) { return std::isdigit(c); });
}

auto validate_value(auto const& key_value) -> bool
{
    auto validate_if_exists = [](auto const& data) {
        if (!data)
            return false;
        return validate(*data);
    };
    auto const& [key, value] = key_value;
    switch (key) {
        case Key::byr: return validate_if_exists(parse_birth_year(value));
        case Key::iyr: return validate_if_exists(parse_issue_year(value));
        case Key::eyr: return validate_if_exists(parse_expiration_year(value));
        case Key::hgt: return validate_if_exists(parse_height(value));
        case Key::hcl: return validate_if_exists(parse_hair_color(value));
        case Key::ecl: return validate_if_exists(parse_eye_color(value));
        case Key::pid: return validate_if_exists(parse_passport_id(value));
        case Key::cid: return true;
        case Key::Invalid: return false;
    }
    return false;
}

auto validate_values(auto const& keys_values) -> bool
{
    return std::ranges::all_of(keys_values,
                               [](auto const& x) { return validate_value(x); });
}

inline auto get_valid_count_part_ii(std::string const& filename) -> int
{
    auto count = 0;
    auto file  = std::ifstream{filename};
    while (file) {
        auto const passport    = get_passport_string(file);
        auto const keys_values = parse_keys_values(passport);
        if (!validate_keys(keys_values))
            continue;
        if (!validate_values(keys_values))
            continue;
        ++count;
    }
    return count;
}

#endif  // DAY_04_COMMON_HPP
