cmake_minimum_required(VERSION 3.14)
project(AdventOfCode2020)

add_compile_options(-Wall -Wextra -std=c++20)

add_executable(day1.1 day_01/one.main.cpp)
add_executable(day1.2 day_01/two.main.cpp)

add_executable(day2.1 day_02/one.main.cpp)
add_executable(day2.2 day_02/two.main.cpp)
