cmake_minimum_required(VERSION 3.0.0)
project(longwrite VERSION 0.1.0)

set(EXECUTABLE_OUTPUT_PATH "bin")
add_executable(longwrite main.cpp)
set_property(TARGET longwrite PROPERTY CXX_STANDARD 11)