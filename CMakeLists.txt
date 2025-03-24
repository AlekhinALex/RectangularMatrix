cmake_minimum_required(VERSION 3.10)
project(lab1_rectangularMatri)

file(GLOB SOURCES "source/*.c")
file(GLOB HEADERS "inc/*.h")

add_executable(lab1_rectangularMatri ${SOURCES} ${HEADERS})
target_include_directories(lab1_rectangularMatri PRIVATE inc)
