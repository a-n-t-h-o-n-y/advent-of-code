#ifndef DAY_11_COMMON_HPP
#define DAY_11_COMMON_HPP
#include <algorithm>
#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

/// Top left is {0, 0}.
class Matrix {
   public:
    void set_width(std::size_t w) { width_ = w; }

    auto width() const -> std::size_t { return width_; }

    void set_height(std::size_t h) { height_ = h; }

    auto height() const -> std::size_t { return height_; }

    auto at(std::size_t x, std::size_t y) const -> char
    {
        return data_[index(x, y)];
    }

    auto at(std::size_t x, std::size_t y) -> char&
    {
        return data_[index(x, y)];
    }

    /// For initialization.
    auto data() -> std::vector<char>& { return data_; }

    friend auto operator==(Matrix const& l, Matrix const& r) -> bool
    {
        return l.data_ == r.data_;
    }

   private:
    std::vector<char> data_;
    std::size_t width_  = 0;
    std::size_t height_ = 0;

   private:
    auto index(std::size_t x, std::size_t y) const -> std::size_t
    {
        return y * width_ + x;
    }
};

inline auto parse(std::istream& is) -> Matrix
{
    auto result = Matrix{};
    auto height = 0uL;
    std::string line;
    while (std::getline(is, line, '\n')) {
        result.set_width(line.size());
        ++height;
        std::ranges::copy(line, std::back_inserter(result.data()));
    }
    result.set_height(height);
    return result;
}

inline auto neighbor_count(Matrix const& m, int x, int y) -> int
{
    auto count           = 0;
    auto const neighbors = std::array{
        std::pair{x, y - 1},     std::pair{x, y + 1},
        std::pair{x + 1, y},     std::pair{x - 1, y},
        std::pair{x - 1, y - 1}, std::pair{x + 1, y - 1},
        std::pair{x - 1, y + 1}, std::pair{x + 1, y + 1},
    };

    auto const valid = [&m](auto const& n) {
        return n.first >= 0 && n.first < (int)m.width() && n.second >= 0 &&
               n.second < (int)m.height();
    };

    for (auto const& n : neighbors) {
        if (valid(n))
            if (m.at(n.first, n.second) == '#')
                ++count;
    }
    return count;
}

inline auto step(Matrix const& m) -> Matrix
{
    auto result = m;
    for (auto x = 0uL; x < m.width(); ++x) {
        for (auto y = 0uL; y < m.height(); ++y) {
            switch (m.at(x, y)) {
                case 'L':
                    if (neighbor_count(m, x, y) == 0)
                        result.at(x, y) = '#';
                    break;
                case '#':
                    if (neighbor_count(m, x, y) > 3)
                        result.at(x, y) = 'L';
                    break;
                default: break;
            }
        }
    }
    return result;
}

inline auto solution_1(std::string const& filename) -> int
{
    auto file   = std::ifstream(filename);
    auto input  = parse(file);
    auto output = input;
    do {
        input  = output;
        output = step(input);
    } while (input != output);
    return std::ranges::count(output.data(), '#');
}

// Part II ---------------------------------------------------------------------

inline auto find_nearest(Matrix const& m,
                         int x,
                         int y,
                         std::pair<int, int> direction) -> char
{
    auto const increment = [&direction](int& x, int& y) {
        x += direction.first;
        y += direction.second;
    };
    char result = '\0';
    while (result != 'L' && result != '#') {
        increment(x, y);
        if (x >= 0 && x < (int)m.width() && y >= 0 && y < (int)m.height()) {
            result = m.at(x, y);
        }
        else
            return '\0';
    }
    return result;
}

inline auto new_neighbor_count(Matrix const& m, int x, int y) -> int
{
    auto count                = 0;
    auto constexpr directions = std::array{
        std::pair{0, -1},  std::pair{0, 1},  std::pair{1, 0},  std::pair{-1, 0},
        std::pair{-1, -1}, std::pair{1, -1}, std::pair{-1, 1}, std::pair{1, 1},
    };

    for (auto const& d : directions) {
        char const nearest = find_nearest(m, x, y, d);
        if (nearest == '#')
            ++count;
    }
    return count;
}

inline auto new_step(Matrix const& m) -> Matrix
{
    auto result = m;
    for (auto x = 0uL; x < m.width(); ++x) {
        for (auto y = 0uL; y < m.height(); ++y) {
            switch (m.at(x, y)) {
                case 'L':
                    if (new_neighbor_count(m, x, y) == 0)
                        result.at(x, y) = '#';
                    break;
                case '#':
                    if (new_neighbor_count(m, x, y) > 4)
                        result.at(x, y) = 'L';
                    break;
                default: break;
            }
        }
    }
    return result;
}

inline auto solution_2(std::string const& filename) -> int
{
    auto file   = std::ifstream(filename);
    auto input  = parse(file);
    auto output = input;
    do {
        input  = output;
        output = new_step(input);
    } while (input != output);
    return std::ranges::count(output.data(), '#');
}

#endif  // DAY_11_COMMON_HPP
