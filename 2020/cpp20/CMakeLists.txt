cmake_minimum_required(VERSION 3.14)
project(AdventOfCode2020)

add_compile_options(-Wall -Wextra -std=c++20)

add_library(external INTERFACE)
target_include_directories(external INTERFACE external/)
link_libraries(external)

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

add_executable(day10.1 day_10/one.main.cpp)
add_executable(day10.2 day_10/two.main.cpp)

add_executable(day11.1 day_11/one.main.cpp)
add_executable(day11.2 day_11/two.main.cpp)

add_executable(day12.1 day_12/one.main.cpp)
add_executable(day12.2 day_12/two.main.cpp)

# add_executable(day13.1 day_13/one.main.cpp)
# add_executable(day13.2 day_13/two.main.cpp)

# add_executable(day14.1 day_14/one.main.cpp)
# add_executable(day14.2 day_14/two.main.cpp)

# add_executable(day15.1 day_15/one.main.cpp)
# add_executable(day15.2 day_15/two.main.cpp)

# add_executable(day16.1 day_16/one.main.cpp)
# add_executable(day16.2 day_16/two.main.cpp)

# add_executable(day17.1 day_17/one.main.cpp)
# add_executable(day17.2 day_17/two.main.cpp)

# add_executable(day18.1 day_18/one.main.cpp)
# add_executable(day18.2 day_18/two.main.cpp)

# add_executable(day19.1 day_19/one.main.cpp)
# add_executable(day19.2 day_19/two.main.cpp)

# add_executable(day20.1 day_20/one.main.cpp)
# add_executable(day20.2 day_20/two.main.cpp)

# add_executable(day21.1 day_21/one.main.cpp)
# add_executable(day21.2 day_21/two.main.cpp)

# add_executable(day22.1 day_22/one.main.cpp)
# add_executable(day22.2 day_22/two.main.cpp)

# add_executable(day23.1 day_23/one.main.cpp)
# add_executable(day23.2 day_23/two.main.cpp)

# add_executable(day24.1 day_24/one.main.cpp)
# add_executable(day24.2 day_24/two.main.cpp)

# add_executable(day25.1 day_25/one.main.cpp)
# add_executable(day25.2 day_25/two.main.cpp)
