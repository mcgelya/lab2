set(CMAKE_AUTOMOC ON)

add_executable(main main.cpp utils.cpp column.cpp visualize.cpp)
target_link_libraries(main Qt6::Widgets)
