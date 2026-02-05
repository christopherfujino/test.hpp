cmake_minimum_required(VERSION 3.31)

project(test.hpp-test VERSION 0.1)

# These CMAKE_* variables apply to all future targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate a compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# IWYU
find_program(IWYU_PATH NAMES include-what-you-use iwyu)
if(NOT IWYU_PATH)
  message(FATAL_ERROR "Could not find the program include-what-you-use")
endif()
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})

add_compile_options(-Wall -Werror -Wpedantic -Wextra)

## Test

add_executable(main main.cpp)
target_include_directories(main PRIVATE ..)
