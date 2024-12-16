cmake_minimum_required(VERSION 3.11.0...3.31.2)
project(sleep_sort VERSION 0.1.0 LANGUAGES CXX)

# Set C++20 and create compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sleep_sort main.cpp)
