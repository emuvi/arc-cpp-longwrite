cmake_minimum_required(VERSION 3.0.0)
project(longwrite VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH "bin")

add_executable(longwrite main.cpp)
set_target_properties(longwrite PROPERTIES CXX_STANDARD 17)