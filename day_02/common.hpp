#ifndef DAY_02_COMMON_HPP
#define DAY_02_COMMON_HPP
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

// 1-3 a: abcde
// 1-3 b: cdefg
// 2-9 c: ccccccccc

/// Parse out the min, max, target char, and password from a line.
auto parse_policy(std::string line)
{
    struct Parts {
        int min;
        int max;
        char target;
        std::string password;
    } parts;

    auto ss = std::istringstream{line};
    ss >> parts.min;
    auto abyss = '\0';
    ss >> abyss;
    ss >> parts.max;
    ss >> parts.target;
    ss >> abyss;
    ss >> parts.password;
    return parts;
}

/// Check if a password matches its policy.
auto is_valid(std::string const& policy_password) -> bool
{
    auto const [min, max, target, password] = parse_policy(policy_password);
    auto const n = std::ranges::count(password, target);
    return n >= min && n <= max;
}

/// Check if a password matches it policy, part II.
auto is_actually_valid(std::string const& policy_password) -> bool
{
    auto const [pos1, pos2, target, password] = parse_policy(policy_password);
    return (password[pos1 - 1] == target) != (password[pos2 - 1] == target);
}

#endif  // DAY_02_COMMON_HPP
