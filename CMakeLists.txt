cmake_minimum_required(VERSION 3.10)

project(lab2)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Catch2 3 REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
