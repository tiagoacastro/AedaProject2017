cmake_minimum_required(VERSION 3.8)
project(AEDA_Proj1)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(AEDA_Proj1 ${SOURCE_FILES})