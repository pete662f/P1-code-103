cmake_minimum_required(VERSION 3.20)
project(MyProject C)

# Specify the C standard
set(CMAKE_C_STANDARD 11)

# Add source files
add_executable(main main.c functions.c)

add_executable(test test.c CuTest.c functions.c)
