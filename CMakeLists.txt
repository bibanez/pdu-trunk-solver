cmake_minimum_required(VERSION 3.10)

# Project name
project(TrunkSolver VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set clangd compatibility
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add compiler flags
add_compile_options(-Wall -Wextra -O3 -g)

add_executable(trunk-solver main.cc types.h types.cc)
