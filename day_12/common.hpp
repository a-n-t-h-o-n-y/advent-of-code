#ifndef DAY_12_COMMON_HPP
#define DAY_12_COMMON_HPP
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

struct Instruction {
    char direction;
    int value;
};

auto parse(std::istream& is) -> std::vector<Instruction>
{
    auto result      = std::vector<Instruction>{};
    auto instruction = Instruction{};
    while (is >> instruction.direction, is >> instruction.value)
        result.push_back(instruction);
    return result;
}

struct Coordinates {
    int x;
    int y;
};

struct State {
    Coordinates position;
    char direction;  // the ship is facing
};

auto manhattan_distance(Coordinates a, Coordinates b) -> int
{
    return std::abs(b.x - a.x) + std::abs(b.y - a.y);
}

/// Returns a new direction. E -> N -> W -> S
auto turn_left(char direction, int degrees) -> char
{
    auto const count = (degrees / 90) % 4;
    for (auto i = 0; i < count; ++i) {
        switch (direction) {
            case 'E': direction = 'N'; break;
            case 'N': direction = 'W'; break;
            case 'W': direction = 'S'; break;
            case 'S': direction = 'E'; break;
        }
    }
    return direction;
}

/// Returns a new direction. E -> S -> W -> N
auto turn_right(char direction, int degrees) -> char
{
    auto const count = (degrees / 90) % 4;
    for (auto i = 0; i < count; ++i) {
        switch (direction) {
            case 'E': direction = 'S'; break;
            case 'S': direction = 'W'; break;
            case 'W': direction = 'N'; break;
            case 'N': direction = 'E'; break;
        }
    }
    return direction;
}

auto step(Instruction i, State s) -> State
{
    switch (i.direction) {
        case 'N': s.position.y -= i.value; break;
        case 'S': s.position.y += i.value; break;
        case 'E': s.position.x += i.value; break;
        case 'W': s.position.x -= i.value; break;
        case 'L': s.direction = turn_left(s.direction, i.value); break;
        case 'R': s.direction = turn_right(s.direction, i.value); break;
        case 'F': s = step({s.direction, i.value}, s); break;
    }
    return s;
}

auto solution_1(std::string const& filename) -> int
{
    auto file         = std::ifstream(filename);
    auto instructions = parse(file);
    auto const start  = Coordinates{0, 0};
    auto state        = State{start, 'E'};
    for (auto instruction : instructions)
        state = step(instruction, state);
    return manhattan_distance(start, state.position);
}

// Part II ---------------------------------------------------------------------

// hold the waypoint, update the waypoint with a step method
// hold your own position, move your position with state as well
// three pieces of data to step on

using Waypoint = Coordinates;

struct State2 {
    State s;
    Waypoint wp;
};

/// Move start towards destination n times
auto forward(Coordinates start, Waypoint destination, int n) -> Coordinates
{
    start.x += destination.x * n;
    start.y += destination.y * n;
    return start;
}

auto rotate_left_once(Waypoint wp) -> Waypoint { return {wp.y, wp.x * -1}; }

auto rotate_left(Waypoint wp, int degrees) -> Waypoint
{
    auto const count = (degrees / 90) % 4;
    for (auto i = 0; i < count; ++i)
        wp = rotate_left_once(wp);
    return wp;
}

auto rotate_right_once(Waypoint wp) -> Waypoint { return {wp.y * -1, wp.x}; }

auto rotate_right(Waypoint wp, int degrees) -> Waypoint
{
    auto const count = (degrees / 90) % 4;
    for (auto i = 0; i < count; ++i)
        wp = rotate_right_once(wp);
    return wp;
}

auto step2(Instruction i, State2 s) -> State2
{
    std::cout << "start: waypoint x: " << s.wp.x << " y: " << s.wp.y << '\n';
    std::cout << "ship x: " << s.s.position.x << " y: " << s.s.position.y << '\n';
    switch (i.direction) {
        case 'N': s.wp.y -= i.value; break;
        case 'S': s.wp.y += i.value; break;
        case 'E': s.wp.x += i.value; break;
        case 'W': s.wp.x -= i.value; break;
        case 'L': s.wp = rotate_left(s.wp, i.value); break;
        case 'R': s.wp = rotate_right(s.wp, i.value);break;
        case 'F': s.s.position = forward(s.s.position, s.wp, i.value); break;
    }
    std::cout << "end: waypoint x: " << s.wp.x << " y: " << s.wp.y << '\n';
    std::cout << "ship x: " << s.s.position.x << " y: " << s.s.position.y << '\n';
    return s;
}

auto solution_2(std::string const& filename) -> int
{
    auto file         = std::ifstream(filename);
    auto instructions = parse(file);

    auto const start = Coordinates{0, 0};
    auto state       = State2{{start, 'E'}, {10, -1}};
    for (auto instruction : instructions)
        state = step2(instruction, state);
    return manhattan_distance(start, state.s.position);
}

#endif  // DAY_12_COMMON_HPP
