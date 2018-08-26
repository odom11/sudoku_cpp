cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(sudoku)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(BEFORE ../include ${BOOST_INCLUDE_DIRS})

add_executable(fooTest fooTest.cpp )
target_link_libraries(fooTest ${Boost_LIBRARIES})

add_executable(sudokuSolverTest sudokuSolverTest.cpp ../src/SudokuSolver.cpp )
target_link_libraries(sudokuSolverTest ${Boost_LIBRARIES})

add_executable(sudokuSolverLeastOptionsTest sudokuSolverLeastOptionsTest.cpp ../src/SudokuSolver.cpp ../src/SudokuSolverLeastOptions.cpp )
target_link_libraries(sudokuSolverLeastOptionsTest ${Boost_LIBRARIES})



