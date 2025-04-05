cmake_minimum_required(VERSION 3.10)
project(lab1)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "source/*.c")
file(GLOB HEADERS "inc/*.h")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS} inc)

add_executable(lab1
    source/main.c
    source/matrix.c
    source/errorHandling.c
    source/integer.c
    source/inputHandling.c
    source/complex.c
    source/double.c
)

add_executable(googleTests
    source/googleTests.cpp
    source/matrix.c
    source/errorHandling.c
    source/integer.c
    source/inputHandling.c
    source/complex.c
    source/double.c
)

# Link GoogleTest
target_link_libraries(googleTests GTest::GTest GTest::Main pthread)
