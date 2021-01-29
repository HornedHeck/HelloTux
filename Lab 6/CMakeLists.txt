cmake_minimum_required(VERSION 3.1)

project(L6)

set(CMAKE_CXX_STANDARD 20)

add_executable(L6 main.cpp ../morze_converter/converter.cpp ../morze_converter/converter.h)

find_library(PTHREAD_LIBRARY pthread)

target_link_libraries(L6 ${PTHREAD_LIBRARY})