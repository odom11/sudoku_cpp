//
// Created by ich on 8/26/18.
//

#include <SudokuSolverLeastOptions.h>


int main() {
    std::string testString = "030000000000195000008000060800060000400800001000020000060000280000419005000000070";
    SudokuSolverLeastOptions solver;
    solver.initialize(testString);

    std::cout << "input sudoku: " << std::endl << solver.getField() << std::endl << "solving ..." << std::endl;

    if (solver.solve()) {
        std::cout << "solved input sudoku" << std::endl;
        std::cout << solver.getField();
    } else {
        std::cout << "input sudoku is not solvable" << std::endl;
    }
}
