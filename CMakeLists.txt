cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 20)

project(senc)
file(GLOB_RECURSE SRCS compiler/*.cpp)
add_executable(${PROJECT_NAME} ${SRCS})