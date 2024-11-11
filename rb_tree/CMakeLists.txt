
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
# set the project name

project(rb
VERSION 1.0
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(test_rb tests/test_rb.cpp src/rb.cpp src/rbNode.cpp)
add_executable(test_abb tests/test_abb.cpp src/abbNode.cpp src/abb.cpp)
add_executable(test_avl tests/test_avl.cpp src/avlNode.cpp src/avl.cpp)

target_include_directories(test_rb PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(test_abb PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(test_avl PUBLIC ${PROJECT_SOURCE_DIR}/include)


# add the executable