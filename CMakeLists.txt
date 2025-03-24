cmake_minimum_required(VERSION 3.10)
project(lab1)

file(GLOB SOURCES "source/*.c")
file(GLOB HEADERS "inc/*.h")

add_executable(lab1
    source/main.c
    source/matrix.c
    source/errorHandling.c
    source/integer.c
    source/inputHandling.c
    source/complex.c
    source/double.c
)

add_executable(tests
    source/testMatrix.c
    source/matrix.c
    source/errorHandling.c 
    source/matrix.c
    source/errorHandling.c
    source/integer.c
    source/inputHandling.c
    source/complex.c
    source/double.c
    
)
target_include_directories(lab1 PRIVATE inc)
