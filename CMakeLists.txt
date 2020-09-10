cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall -j32 -pthread")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SnakeRoyale)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

INCLUDE(FindPkgConfig)

find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} src)

file(GLOB project_SRC "src/*.cpp")
add_executable(SnakeRoyale ${project_SRC})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SnakeRoyale ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})