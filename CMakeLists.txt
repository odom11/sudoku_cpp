cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(sudoku)

include_directories(BEFORE include)
FILE(GLOB_RECURSE myfiles  src/*.cpp)
add_executable(main ${myfiles})


enable_testing()
add_subdirectory("./test")
add_test(NAME testFoo COMMAND fooTest)
add_test(NAME testSudokuSolver COMMAND sudokuSolverTest)
add_test(NAME testSudokuSolverLeastOptions COMMAND sudokuSolverLeastOptionsTest)
