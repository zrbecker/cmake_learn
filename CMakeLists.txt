cmake_minimum_required(VERSION 3.3.0)

project(cmake_learn)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(fruit REQUIRED)
find_package(gtest REQUIRED)

add_subdirectory(examples/hello_world)
add_subdirectory(resources)
add_subdirectory(src/game)
add_subdirectory(src/playground)
add_subdirectory(src/tests)
