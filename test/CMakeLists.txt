cmake_minimum_required(VERSION 3.0)

project(hello LANGUAGES CXX)

add_subdirectory(hello)

include_directories(hello)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC hello)

