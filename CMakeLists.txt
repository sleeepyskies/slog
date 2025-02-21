cmake_minimum_required(VERSION 3.29)
project(slog)

set(CMAKE_CXX_STANDARD 20)

add_library(slog STATIC slog.hpp)

set_target_properties(slog PROPERTIES LINKER_LANGUAGE CXX)