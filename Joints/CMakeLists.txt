cmake_minimum_required(VERSION 3.26)
project(Joints)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(Joints main.cpp
        DistanceJoint.cpp
        RevoluteJoint.cpp
        PrismaticJoint.cpp
        GearJoint.cpp
        WeldJoint.cpp)
find_package(box2d CONFIG REQUIRED)
target_link_libraries(Joints PRIVATE box2d::box2d PRIVATE sfml-system PRIVATE sfml-window PRIVATE sfml-graphics PRIVATE sfml-audio)