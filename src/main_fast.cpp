//
// Created by ich on 8/26/18.
//

#include <SudokuSolverLeastOptions.h>

const std::string convertFileContentToSudokuInputString(const char * filename);


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
