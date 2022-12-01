#ifndef DAY_08_COMMON_HPP
#define DAY_08_COMMON_HPP
#include <charconv>
#include <cstddef>
#include <fstream>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

struct Instruction {
    enum Type { acc, jmp, nop };
    Type type;
    int parameter;
};

inline auto get_type(std::string_view instruction) -> Instruction::Type
{
    if (instruction == "acc")
        return Instruction::acc;
    if (instruction == "jmp")
        return Instruction::jmp;
    if (instruction == "nop")
        return Instruction::nop;
    throw std::invalid_argument{std::string{instruction}};
}

/// Parse out a signed int, assumes input is valid.
inline auto get_int(std::string_view x) -> int
{
    if (x.front() == '+')  // std::from_chars will error on this.
        x = x.substr(1);
    auto value = 0;
    std::from_chars(x.data(), x.data() + x.size(), value);
    return value;
}

inline auto parse_line(std::string_view line) -> Instruction
{
    auto result      = Instruction{};
    result.type      = get_type(line.substr(0, 3));
    result.parameter = get_int(line.substr(4));
    return result;
}

using Program = std::vector<Instruction>;

inline auto parse_program(std::istream& is) -> Program
{
    auto result = Program{};
    auto line   = std::string{};
    while (std::getline(is, line, '\n'))
        result.push_back(parse_line(line));
    return result;
}

/// Stores the value of the accumulator and the next line to be executed.
struct State {
    int accumulator;
    std::size_t line_number;
};

/// Executes one instruction and returns a new program state.
inline auto step(Program const& program, State state) -> State
{
    switch (program[state.line_number].type) {
        case Instruction::acc:
            state.accumulator += program[state.line_number].parameter;
            ++state.line_number;
            break;
        case Instruction::jmp:
            state.line_number += program[state.line_number].parameter;
            break;
        case Instruction::nop: ++state.line_number; break;
    }
    return state;
}

inline auto is_end(Program const& program, State state) -> bool
{
    return state.line_number == program.size();
}

/// Stores line numbers that have been executed in a run of a program.
using Lines_executed = std::set<std::size_t>;

// What is the value of the accumulator right before any instruction is
// executed for a second time?
inline auto solution_1(std::string const& filename) -> int
{
    auto file    = std::ifstream{filename};
    auto program = parse_program(file);

    auto history = Lines_executed{};
    auto state   = State{0, 0};
    while (!history.contains(state.line_number)) {
        history.insert(state.line_number);
        state = step(program, state);
    }
    return state.accumulator;
}

// Part II

/// Modify the next nop to a jmp, staring from \p from_line.
/** Return the new program and the line that it modified. */
inline auto modify_nop_to_jmp(Program program, std::size_t from_line)
    -> std::pair<Program, std::size_t>
{
    while (from_line != program.size()) {
        if (program[from_line].type == Instruction::nop) {
            program[from_line].type = Instruction::jmp;
            break;
        }
        ++from_line;
    }
    return {program, from_line};
}

/// Modify the next jmp to a nop, staring from \p from_line.
/** Return the new program and the line that it modified. */
inline auto modify_jmp_to_nop(Program program, std::size_t from_line)
    -> std::pair<Program, std::size_t>
{
    while (from_line != program.size()) {
        if (program[from_line].type == Instruction::jmp) {
            program[from_line].type = Instruction::nop;
            break;
        }
        ++from_line;
    }
    return {program, from_line};
}

/// Runs the program through completion and returns the accumulator value.
/** Returns std::nullopt if program does not terminate. */
inline auto run(Program const& program) -> std::optional<int>
{
    auto history = Lines_executed{};
    auto state   = State{0, 0};
    while (!is_end(program, state)) {
        if (history.contains(state.line_number))
            return std::nullopt;
        history.insert(state.line_number);
        state = step(program, state);
    }
    return state.accumulator;
}

/// Fixes a single nop or jmp instruction to stop an inf. loop.
/** Returns the accumulator value of the fixed program after a run. */
inline auto fix_program(Program const& program) -> int
{
    // nop to jmp
    auto modify_from = 0uL;
    while (modify_from < program.size()) {
        auto const [new_program, modified_at] =
            modify_nop_to_jmp(program, modify_from);
        modify_from       = modified_at + 1;
        auto const result = run(new_program);
        if (result)
            return *result;
    }

    // jmp to nop
    modify_from = 0uL;
    while (modify_from < program.size()) {
        auto const [new_program, modified_at] =
            modify_jmp_to_nop(program, modify_from);
        modify_from       = modified_at + 1;
        auto const result = run(new_program);
        if (result)
            return *result;
    }
    return 0;
}

inline auto solution_2(std::string const& filename) -> int
{
    auto file    = std::ifstream{filename};
    auto program = parse_program(file);
    return fix_program(program);
}

#endif  // DAY_08_COMMON_HPP
