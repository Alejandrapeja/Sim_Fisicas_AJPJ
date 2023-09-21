cmake_minimum_required(VERSION 3.26)
project(Hola_Mundo)

set(CMAKE_CXX_STANDARD 17)

add_executable(Hola_Mundo main.cpp)

find_package(box2d CONFIG REQUIRED)
target_link_libraries(Hola_Mundo PRIVATE box2d::box2d)