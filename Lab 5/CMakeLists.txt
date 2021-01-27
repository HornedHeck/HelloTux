cmake_minimum_required(VERSION 3.1)

project(L5)

set(CMAKE_CXX_STANDARD 20)

add_executable(L5 main.cpp executor.h executor.cpp)

find_library(PTHREAD_LIBRARY pthread)

target_link_libraries(L5 ${PTHREAD_LIBRARY})

