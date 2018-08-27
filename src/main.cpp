//
// Created by ich on 8/26/18.
//

#include <SudokuSolverLeastOptions.h>
#include <fstream>

const std::string convertFileContentToSudokuInputString(const char * filename) {
    std::ifstream fileInput(std::string(filename), std::ios::in);
    std::string numberAsString;
    numberAsString.resize(81);
    int index = 0;
    int readNumber = 0;
    if (fileInput.is_open()) {
        while (fileInput >> readNumber ) {
            if(index >= 81) {
                throw std::out_of_range("amount of numbers in input exceeds 81 (number of fields in a sudoku)");
            }
            numberAsString[index++] = readNumber + '0';
        }
        if (index != 81) {
            throw std::out_of_range("expected 81 numbers in file");
        }

        return numberAsString;
    } else {
        throw std::runtime_error("file '" + std::string(filename) + "' could not be opened");
    }

}


int main(int iargc, char * iargv[]) {
    if (iargc != 2) {
        throw std::runtime_error("expected file to sudoku input as commandline argument");
    }
    const std::string sudokuAsString = convertFileContentToSudokuInputString(iargv[1]);

    std::cout << "reading from file '" << std::string(iargv[1]) << "'" << std::endl;

    SudokuSolver&& solver = SudokuSolverLeastOptions();
    solver.initialize(sudokuAsString);

    std::cout << "input sudoku: " << std::endl << solver.getField() << std::endl << "solving ..." << std::endl;

    if (solver.solve()) {
        std::cout << "solved input sudoku" << std::endl;
        std::cout << solver.getField();
    } else {
        std::cout << "input sudoku is not solvable" << std::endl;
    }
}
