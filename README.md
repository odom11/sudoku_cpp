# Sudokusolver
## General
Simple commandline tool to solve a sudoku puzzle with digits from 1 to 9 on a 9x9 grid
## Requirements
- C++ compiler that supports at least C++14
- cmake version 3.10 (feel free to edit the CMakeLists.txt to lower the requirements, but
it might generate problems with the unit tests
- Boost (the unit test framework is required)
## Installation
Create a build folder and run cmake /path/to/CMakeLists.txt. Move the exe wherever you like
## Usage
### how to use the program
enter
./main /path/to/inputfile
in the commandline
### input file requirements
- provide 81 space separated single digits ranging from 0 to 9
- 0 represents an unfilled field
- 1 to 9 represent numbers present in a sudoku
- the file is read from left to right and from top to bottom
- in that order, the sudoku field is filled
- there MUST be 81 numbers in the file

## License
MIT 
