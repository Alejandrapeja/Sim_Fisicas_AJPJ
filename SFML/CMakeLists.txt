cmake_minimum_required(VERSION 3.26)
project(SFML)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)

add_executable(SFML main.cpp)

#Box2D
find_package(box2d CONFIG REQUIRED)
target_link_libraries(SFML PRIVATE box2d::box2d PRIVATE sfml-graphics)