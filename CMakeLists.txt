cmake_minimum_required(VERSION 3.14)
project(AdventOfCode2020)

add_compile_options(-Wall -Wextra -std=c++20)

add_executable(day1.1 day_01/one.main.cpp)
add_executable(day1.2 day_01/two.main.cpp)

add_executable(day2.1 day_02/one.main.cpp)
add_executable(day2.2 day_02/two.main.cpp)

add_executable(day3.1 day_03/one.main.cpp)
add_executable(day3.2 day_03/two.main.cpp)
add_executable(day3.r day_03/ranges.main.cpp)

add_executable(day4.1 day_04/one.main.cpp)
add_executable(day4.2 day_04/two.main.cpp)

add_executable(day5.1 day_05/one.main.cpp)
add_executable(day5.2 day_05/two.main.cpp)

add_executable(day6.1 day_06/one.main.cpp)
add_executable(day6.2 day_06/two.main.cpp)

add_executable(day7.1 day_07/one.main.cpp)
add_executable(day7.2 day_07/two.main.cpp)

add_executable(day8.1 day_08/one.main.cpp)
add_executable(day8.2 day_08/two.main.cpp)

add_executable(day9.1 day_09/one.main.cpp)
add_executable(day9.2 day_09/two.main.cpp)
