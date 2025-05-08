set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=undefined,address")

add_executable(main main.cpp)
target_link_libraries(main Qt6::Widgets)
