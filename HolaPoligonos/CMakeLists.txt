cmake_minimum_required(VERSION 3.26)
project(HolaPoligonos)

set(CMAKE_CXX_STANDARD 17)

add_executable(HolaPoligonos main.cpp)

find_package(box2d CONFIG REQUIRED)
target_link_libraries(HolaPoligonos PRIVATE box2d::box2d)